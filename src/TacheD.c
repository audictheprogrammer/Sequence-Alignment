#include "Outils.h"

char* gaps(int k){
    char* x = (char*) malloc(sizeof(char)*k);
    for (int i = 0; i < k; i++){
        x[i] = '-';
    }
    return x;
}

char** align_lettre_mot(char* x, char* y){
    int m = strlen(y);
    int i0 = -1;

    // Determine s'il est existe concordant de x dans y
    for (int i = 0; i < m; i++){
        if (x[0] == y[i]){
            char* res = (char*) malloc(sizeof(char)*(m+1));
            strcpy(res, gaps(i));
            strcat(res, x);
            strcat(res, gaps(m-i-1));
            return couple(res, y);
        }
        if (C_SUB(y[i], x[0]) == 3){
            i0 = i;
        }
    }

    if (i0 != -1){
        // Convertir y[i0] en une chaine de caractere
        char y[2];
        y[0] = y[i0];
        y[1] = '\0';

        char* res = (char*) malloc(sizeof(char)*(m+1));
        strcpy(res, gaps(i0));
        strcat(res, y);
        strcat(res, gaps(m-i0-1));
        return couple(res, y);
    }

    return couple(strcat(x, gaps(m-1)), y);
}

int coupure(char* x, char*y){
    int n = strlen(x);
    int m = strlen(y);
    int i_ = n/2;
    int* Tc = (int*) malloc(sizeof(int) * (m + 1));
    int* T = (int*) malloc(sizeof(int) * (m + 1));
    int* Ic = (int*) malloc(sizeof(int) * (m + 1));
    int* I = (int*) malloc(sizeof(int) * (m + 1));
    for (int i = 0; i <= m; i++){
        T[i] = i * c_ins;
        I[i] = i;
    }
    for (int i = 1; i <= n; i++){
        Tc[0] = i * c_del;
        for (int j = 1; j <= m; j++){
            int A = Tc[j-1] + c_ins;
            int B = T[j] + c_del;
            int C = T[j-1] + C_SUB(x[i-1], y[j-1]);
            Tc[j] = min(A,B,C);
            if (i > i_){
                if(Tc[j] == A){
                    Ic[j] = Ic[j-1];
                }
                if(Tc[j] == B){
                    Ic[j] = I[j];
                }
                if(Tc[j] == C){
                    Ic[j] = I[j-1];
                }
            }
        }
        for (int i = 0; i <= m; i++) {
            T[i] = Tc[i];
            if (i > i_){
                I[i] = Ic[i];
            }
        }
    }
    return Ic[m];
}

char** sol_2(char* x, char* y){
    int n = strlen(x);
    int m = strlen(y);
    if (n == 0){
        return couple(gaps(m),y);
    }
    if (m == 0){
        return couple(x, gaps(n));
    }
    if (n == 1){
        return align_lettre_mot(x,y);
    }
    if (n == 0){
        return align_lettre_mot(y,x);
    }
    int i_ = n/2;
    int j_ = coupure(x,y);

    char** s = sol_2(recup(x, 0, i_-1), recup(y, 0, j_-1));
    char** u = sol_2(recup(x, i_, n-1), recup(y, j_, m-1));

    return couple(strcat(s[0],u[0]), strcat(s[1],u[1]));
}

void teste_instance(char* nom_fichier) {
    /* Teste une seule instance.*/
    int n;
    char** mots = lire_fichier(nom_fichier, &n);
    printf("\nPour (x = %s, y = %s): \n", mots[0], mots[1]);
    char** align = sol_2(mots[0], mots[1]);

    char* u = align[0];
    char* v = align[1];
    printf("Align renvoie: (u = %s, v = %s): \n", align[0], align[1]);

}


void performance(const char nom_fichier[], FILE* F_OUT) {
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;

    int strlen_x;
    char** mots = lire_fichier(nom_fichier, &strlen_x);
    temps_initial = clock ();

    char** align = sol_2(mots[0], mots[1]);

    temps_final = clock ();
    temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;

    fprintf(F_OUT, "%d %f \n", strlen_x, temps_cpu);
    printf("%d %f \n", strlen_x, temps_cpu);
}

char** lire_repertoire(char* nom_repertoire, int* nb_fichiers) {
    /* Renvoie tous les noms de fichiers d'un repertoire
    Et met a jour la valeur de nb_fichier.
    */
    struct dirent* pDirent;
    DIR* pDir = opendir(nom_repertoire);

    // Determine le nombre de fichier.
    *nb_fichiers = 0;
    while ((pDirent = readdir(pDir)) != NULL) {
        if (strlen(pDirent->d_name) > 2) {
            (*nb_fichiers)++;
        }
    }

    // Il ya nb_fichiers dans le repertoire (58 pour Instances_genome)
    char** noms_fichiers = (char**) malloc(sizeof(char*) * *nb_fichiers);

    pDir = opendir(nom_repertoire);  // reset pDirent
    int i = 0;
    while ((pDirent = readdir(pDir)) != NULL) {
        char* nom_fichier = pDirent->d_name;
        if (strlen(nom_fichier) > 2) {
            noms_fichiers[i] = (char*) malloc(sizeof(char) * (18 + strlen(nom_fichier)));
            strcpy(noms_fichiers[i], "Instances_genome/");
            strcat(noms_fichiers[i], nom_fichier);
            printf("nom_fichier = : %s \n", noms_fichiers[i]);
            i++;
        }
    }
    closedir(pDir);
    return noms_fichiers;
}


int main(int argc, char** argv) {
    // int nb_fichiers = 0;
    // char** repertoire = lire_repertoire("Instances_genome/", &nb_fichiers);
    //
    // FILE* f = fopen("Output_D.txt", "w");
    // for (int i = 0; i < nb_fichiers; i++) {
    //     // printf("\nfichier: %s \n", repertoire[i]);
    //     performance(repertoire[i], f);
    // }
    // fclose(f);

    if (argc == 2) {
        teste_instance(argv[1]);
    }
    // ./mainD Instances_genome/Inst_0000013_45.adn

    return 0;
}
