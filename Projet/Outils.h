#ifndef OUTILS_H
#define OUTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>


extern int c_ins;
extern int c_del;
extern int c_sub1;
extern int c_sub2;
extern char* alpha1;
extern int len_alpha1;
extern char* alpha2;
extern int len_alpha2 ;
extern int INT_MAX;


int C_SUB(char x, char y);
int min(int a, int b, int c);
char** lire_fichier(const char nom_fichier[], int* n);
char* renverse(char* x);
char* recup(char* x, int deb, int fin);
char** couple(char* x, char* y);
char* concatener(char* mot1, char* mot2);

#endif