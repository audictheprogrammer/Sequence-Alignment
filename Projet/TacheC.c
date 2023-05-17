#include "Outils.h"


int DIST_2(char* x, char* y) {
    int n = strlen(x);
    int m = strlen(y);
    int* Tc = (int*) malloc(sizeof(int) * (m + 1));
    int* T = (int*) malloc(sizeof(int) * (m + 1));

    // Premiere ligne
    for (int j = 0; j <= m; j++){
        T[j] = j * c_ins;
    }
    for (int i = 1; i <= n; i++){
        Tc[0] = i * c_del;
        for (int j = 1; j <= m; j++){
            int A = Tc[j-1] + c_ins;
            int B = T[j] + c_del;
            int C = T[j-1] + C_SUB(x[i-1], y[j-1]);
            Tc[j] = min(A,B,C);
        }
        for (int i = 0; i <= m; i++) {
            T[i] = Tc[i];
        }
    }
    return Tc[m];
}

void teste_instance(char* nom_fichier) {
    /* Teste une seule instance.*/
    int n;
    char** mots = lire_fichier(nom_fichier, &n);
    int D = DIST_2(mots[0], mots[1]);
    printf("Pour (x = %s, y = %s): \n", mots[0], mots[1]);
    printf("D = %d\n\n", D);
}


void performance(const char nom_fichier[], FILE* F_OUT) {
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;

    int strlen_x;
    char** mots = lire_fichier(nom_fichier, &strlen_x);
    temps_initial = clock ();

    int distance = DIST_2(mots[0], mots[1]);

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
    // FILE* f = fopen("Output_C.txt", "w");
    // for (int i = 0; i < nb_fichiers; i++) {
    //     // printf("\nfichier: %s \n", repertoire[i]);
    //     performance(repertoire[i], f);
    // }
    // fclose(f);

    if (argc == 2) {
        teste_instance(argv[1]);
    }
    // ./mainC Instances_genome/Inst_0000013_45.adn
    return 0;
}
