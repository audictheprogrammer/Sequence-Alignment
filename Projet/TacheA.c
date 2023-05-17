#include "Outils.h"


int DIST_NAIF_REC(char* x, char* y, int i, int j, int c, int dist) {
    if (i == strlen(x) && j == strlen(y)) {
        if (c < dist)
            dist = c;
    }
    else {
        int nb1 = INT_MAX, nb2 = INT_MAX, nb3 = INT_MAX;
        if (i < strlen(x) && j < strlen(y))
            nb1 = DIST_NAIF_REC(x, y, i+1, j+1, c + C_SUB(x[i], y[j]), dist);
        if (i < strlen(x))
            nb2 = DIST_NAIF_REC(x, y, i+1, j , c + c_del, dist);
        if (j < strlen(y))
            nb3 = DIST_NAIF_REC(x, y, i, j+1, c + c_ins, dist);
        dist = min(nb1, nb2, nb3);
    }
    return dist;

}


int DIST_NAIF(char* x, char* y) {
    return DIST_NAIF_REC(x, y, 0, 0, 0, INT_MAX);
}


void teste_instance(char* nom_fichier) {
    /* Teste une seule instance.*/
    int n;
    char** mots = lire_fichier(nom_fichier, &n);
    int D = DIST_NAIF(mots[0], mots[1]);
    printf("Pour (x = %s, y = %s): \n", mots[0], mots[1]);
    printf("D = %d \n\n", D);
}

void performance(char** noms_fichier, char* sortie_fichier, int n) {
    clock_t temps_initial;
    clock_t temps_final;
    double temps_cpu;
    FILE *f = fopen(sortie_fichier, "w");

    for (int i = 0; i < n; i++){
        int n;
        char** mots = lire_fichier(noms_fichier[i], &n);
        temps_initial = clock ();

        DIST_NAIF(mots[0], mots[1]);

        temps_final = clock ();
        temps_cpu = (( double ) ( temps_final - temps_initial ) ) / CLOCKS_PER_SEC ;

        fprintf(f, "%d %f \n", n, temps_cpu);
        printf("%d %ld %f \n", n , strlen(mots[1]), temps_cpu);
    }
}


int main(int argc, char** argv) {
    /* Test de validite pour CSUB, valide.
    printf("CSUB(T, A) = %d \n", C_SUB('T', 'A'));  // 3
    printf("CSUB(A, T) = %d \n", C_SUB('A', 'T'));  // 3
    printf("CSUB(A, A) = %d \n", C_SUB('A', 'A'));  // 0
    printf("CSUB(A, G) = %d \n", C_SUB('A', 'G'));  // 4
    printf("CSUB(A, C) = %d \n", C_SUB('A', 'C'));  // 4
    */

    // Une instance simple, de cout 0.
    // char* x = strdup("TC");
    // char* y = strdup("TC");
    // printf("DIST_NAIF(%s, %s): %d\n", x, y, DIST_NAIF(x, y));

    // teste_instance("Instances_genome/Inst_0000010_44.adn");
    // // De cout 10
    // teste_instance("Instances_genome/Inst_0000010_7.adn");
    // // De cout 8
    // teste_instance("Instances_genome/Inst_0000010_8.adn");
    // // De cout 2

    // Performance pour des instances de tailles 13, 14 et 15.
    // char** liste_nom_fichier = (char**) malloc(sizeof(char*) * 9);
    // liste_nom_fichier[0] = "Instances_genome/Inst_0000013_45.adn";
    // liste_nom_fichier[1] = "Instances_genome/Inst_0000013_56.adn";
    // liste_nom_fichier[2] = "Instances_genome/Inst_0000013_89.adn";
    // liste_nom_fichier[3] = "Instances_genome/Inst_0000014_7.adn";
    // liste_nom_fichier[4] = "Instances_genome/Inst_0000014_23.adn";
    // liste_nom_fichier[5] = "Instances_genome/Inst_0000014_83.adn";
    // liste_nom_fichier[6] = "Instances_genome/Inst_0000015_2.adn";
    // liste_nom_fichier[7] = "Instances_genome/Inst_0000015_4.adn";
    // liste_nom_fichier[8] = "Instances_genome/Inst_0000015_76.adn";
    // performance(liste_nom_fichier, "Output_A.txt", 7);
    //
    // free(liste_nom_fichier);

    if (argc == 2) {
        teste_instance(argv[1]);
    }
    // ./mainA Instances_genome/Inst_0000013_45.adn


    return 0;
}
