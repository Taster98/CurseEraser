/**
 * Blaspheme eliminator: Remove standard blasphemies and personal possible comments/print unwanted!
 */
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_DIM 1000

//Prototipo funzione
void replaceAll(char *str, const char **oldWords, const char *newWord, int j);

int main(int argc, char *argv[]){
    //Puntatori ai file 
    if(argc==3 && !strcmp(argv[1],"-i")){
        FILE * letturaDaEliminare;
        FILE * scritturaDaEliminare;
        char buffer[BUFFER_DIM];
        const char *precWords[100] = {"porco dio", "dio cane","dio porco","porcoddio","madonna puttana","gesù cane", "porca madonna", "diocan"};
        char newWord[100] = "BLASPHEMY DELETED";

        //Apertura file
        letturaDaEliminare  = fopen(argv[2], "r");
        scritturaDaEliminare = fopen("newfile.tmp", "w"); 
        
        //fopen() fallita
        if (letturaDaEliminare == NULL || scritturaDaEliminare == NULL){
            printf("\nUnable to open file.\n");
            printf("Please check whether file exists and you have read/write privilege.\n");
            exit(EXIT_SUCCESS);
        }
        int j=0;
        //Read all lines of program
        while ((fgets(buffer, BUFFER_DIM, letturaDaEliminare)) != NULL){   
            j++;
            replaceAll(buffer, precWords, newWord,j);
            fputs(buffer, scritturaDaEliminare);
        }
        fclose(letturaDaEliminare);
        fclose(scritturaDaEliminare);
        remove(argv[2]);
        rename("newfile.tmp", argv[2]);
        printf("\nSuccessfully replaced all occurrences with 'BLASPHEMY DELETED'!\n");
    }else{
        fprintf(stderr,"Error opening file.\nUsage: make\n./B_eliminator -i filename.format\n");
        fflush(stderr);
    }
    return 0;
}
//Replace all occurrences of the blasphemies.
void replaceAll(char *str, const char **oldWords, const char *newWord, int j){
    char *pos, temp[BUFFER_DIM];
    int index = 0;
    int len;
    //Add for
    for(int i=0;i<8;i++){
        len = strlen(oldWords[i]);
        while ((pos = strcasestr(str, oldWords[i])) != NULL){
            strcpy(temp, str);
            fprintf(stdout,"Found blasphemy at line: %d\n",j);
            fflush(stdout);
            index = pos - str;
            str[index] = '\0';
            strcat(str, newWord);
            //oldword[i] found index.
            strcat(str, temp + index + len);
        }
    }
}