#include "Outils.h"


int** DIST_1(char* x, char* y){
    int n = strlen(x);
    int m = strlen(y);
    int** T = (int**) malloc(sizeof(int*) * (n+1));
    for (int i = 0; i <= n; i++){
        T[i] = (int*) malloc(sizeof(int) * (m+1));
    }
    for (int i = 0; i <= n; i++){
        for (int j = 0; j <= m; j++){
            if (i == 0){
                T[i][j] = j*c_ins;
            }
            else if (j == 0){
                T[i][j] = i*c_del;
            }
            else {
            int A = T[i][j-1] + c_ins;
            int B = T[i-1][j] + c_del;
            int C = T[i-1][j-1] + C_SUB(x[i-1], y[j-1]);
            T[i][j] = min(A,B,C);
            }
        }
    }

    return T;
}

char** SOL_1(char* x, char* y, int** T) {
    int n = strlen(x);
    int m = strlen(y);
    char* u = (char*) malloc(sizeof(char) * (n+m));
    char* v = (char*) malloc(sizeof(char) * (n+m));
    int i = n;
    int j = m;

    int index_u = 0;
    int index_v = 0;
    while (i > 0 || j > 0) {
        if (j > 0 && T[i][j] == T[i][j-1] + c_ins){
            u[index_u] = '-';
            v[index_v] = y[j-1];
            index_u++;
            index_v++;
            j--;
        } else if (i > 0 && T[i][j] == T[i-1][j] + c_del) {
            u[index_u] = x[i-1];
            v[index_v] = '-';
            index_u++;
            index_v++;
            i--;
        } else if (i > 0 && j > 0 && T[i][j] == T[i-1][j-1] + C_SUB(x[i-1], y[j-1])){
            u[index_u] = x[i-1];
            v[index_v] = y[j-1];
            index_u++;
            index_v++;
            i--;
            j--;
        } else {
            printf("Bug \n");
            return NULL;
        }
    }

    char* res_u = renverse(u);
    char* res_v = renverse(v);
    free(u);
    free(v);

    char** tab = (char**) malloc(sizeof(char*) * 2);
    tab[0] = res_u;
    tab[1] = res_v;

    return tab;
}

char** PROG_DYN(char* x, char* y, int* D){
    int n = strlen(x);
    int m = strlen(y);
    int** T = DIST_1(x, y);
    *D = T[n][m];
    return SOL_1(x, y, T);
}

void teste_instance(char* nom_fichier) {
    /* Teste une seule instance.*/
    int D = 0;
    int n;
    char** mots = lire_fichier(nom_fichier, &n);
    char** align = PROG_DYN(mots[0], mots[1], &D);
    char* u = align[0];
    char* v = align[1];
    printf("Pour (x = %s, y = %s): \n", mots[0], mots[1]);
    printf("D = %d et (u = %s, v = %s) \n\n", D, u, v);
}

void performance(const char nom_fichier[], FILE* F_OUT) {
    int D = 0;
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;

    int strlen_x;
    char** mots = lire_fichier(nom_fichier, &strlen_x);
    temps_initial = clock ();

    char** align = PROG_DYN(mots[0], mots[1], &D);
    // int** T = DIST_1(mots[0], mots[1]);

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

    // FILE* f = fopen("Output_B_Dist_1.txt", "w");
    // for (int i = 0; i < nb_fichiers; i++) {
    //     // printf("\nfichier: %s \n", repertoire[i]);
    //     performance(repertoire[i], f);
    // }
    // fclose(f);

    // teste_instance("Instances_genome/Inst_0100000_3.adn");
    // teste_instance("Instances_genome/Inst_0100000_11.adn");
    // teste_instance("Instances_genome/Inst_0100000_76.adn");
    // teste_instance("Instances_genome/Inst_0020000_5.adn");

    if (argc == 2) {
        teste_instance(argv[1]);
    }
    // ./mainB Instances_genome/Inst_0000013_45.adn
    
    return 0;
}
