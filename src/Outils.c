#include "Outils.h"

// Variables globales
int c_ins = 2;
int c_del = 2;
int c_sub1 = 3;
int c_sub2 = 4;
char* alpha1 = "AT";
int len_alpha1 = 2;
char* alpha2 = "GC";
int len_alpha2 = 2;
int INT_MAX = 1 << 30;


int C_SUB(char x, char y) {
    if (x == y) {
        return 0;
    }
    int x_in_alpha1 = 0;
    int y_in_alpha1 = 0;

    // x et y sont dans quel alphabet
    for (int i = 0; i < len_alpha1; i++){
        if (x == alpha1[i])
            x_in_alpha1 = 1;
        if (y == alpha1[i])
            y_in_alpha1 = 1;
    }
    if (x_in_alpha1 + y_in_alpha1 == 1) {
        return c_sub2;  // Paire non concordante
    }
    return c_sub1;  // Paire concordante

}

int min(int a, int b, int c) {
    if (a <= b && a <= c)
        return a;
    if (b <= a && b <= c)
        return b;
    if (c <= a && c <= b)
        return c;
    return -1;
}


char** lire_fichier(const char nom_fichier[], int* n){
    /* Renvoie les 2 mots x et y dans un tableau de char*.
    */
    char** res = (char**) malloc(sizeof(char*) * 2);
    /*
    char* dossier = (char*) malloc(sizeof(char)*100);
    strcpy(dossier, "Instances_genome/");
    char* nom = strcat(dossier,nom_fichier);
    */
    FILE* f = fopen(nom_fichier, "r");
    char buffer[100000];

    if (f == NULL) {
        printf("Erreur de fopen dans lire_fichier ! \n");
        return NULL;
    }

    // TAILLE N et M
    int m;
    fgets(buffer, 10, f);
    sscanf(buffer, "%d", n);
    fgets(buffer, 10, f);
    sscanf(buffer, "%d", &m);

    // MOTS X et Y
    char* x = (char*) malloc(sizeof(char) * *n);
    fgets(buffer, 100000, f);
    int i = 0;
    int j = 0;
    while (buffer[j] != '\0') {
        if (buffer[j] != 32 && buffer[j] != 10){
            x[i] = buffer[j];
            i++;
        }
        j++;
    }

    char* y = (char*) malloc(sizeof(char) * m);
    fgets(buffer, 100000, f);
    i = 0;
    j = 0;
    while (buffer[j] != '\0') {
        if (buffer[j] != 32 && buffer[j] != 10){
            y[i] = buffer[j];
            i++;
        }
        j++;
    }

    fclose(f);
    res[0] = x;
    res[1] = y;
    return res;

}


char* renverse(char* x) {
    char* u = (char*) malloc(sizeof(u) * strlen(x));
    if (u == NULL) {
        printf("Probleme avec renverse \n");
        return NULL;
    }

    for (int i = 0; i < strlen(x); i++) {
        u[i] = x[strlen(x) - i - 1];
    }

    return u;
}

char* recup(char* x, int deb, int fin){
    if (deb > fin) {
        return strdup("");
    }
    char* u = (char*) malloc(sizeof(char) * (fin-deb+1));
    for (int i = 0; i < (fin-deb+1); i++){
        u[i] = x[deb+i];
    }
    return u;
}

char** couple(char* x, char* y){
    char** tab = (char**) malloc(sizeof(char*) * 2);
    tab[0] = strdup(x);
    tab[1] = strdup(y);

    return tab;
}

char* concatener(char* mot1, char* mot2) {
    int n = strlen(mot1);
    int m = strlen(mot2);

    char* mot = (char*) malloc(sizeof(char) * (n+m));
    if (mot == NULL) {
        printf("Erreur de malloc dans concat \n");
        return NULL;
    }
    printf("strlen(mot1) = %ld \n", strlen(mot1));
    printf("strlen(mot2) = %ld \n", strlen(mot2));

    for (int i = 0; i < n+m; i++) {
        if (i < n){
            mot[i] = mot1[i];
        }
        else {
            mot[i] = mot2[i-n];
        }
    }

    return mot;
}


// rep = opendir("./Documents fournis/");
//     if (rep){
//         struct dirent *dir;
//         while((temps_cpu < 60) && (dir = readdir(rep))){
//         // pDirent->d_name
//             FILE* f = fopen(dir, "w");
//             void performance(const char nom_fichier[], FILE* F_OUT) {

//         }
