#!/bin/bash
#creation of folders
mkdir error;
mkdir src;
#creation of curseEraser.c
echo \
"\
/**
 * CurseWordEraser: Remove all the unwanted curse words within a source code or any other kind of file!
 */
#define _GNU_SOURCE
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_DIM 1000
#define WORDS_DIM 3000
#define MAXLEN 101

#include \"./error/error.h\"
#include \"./src/utils.h\"

//curseEraser -i inputfile -d dictionary.txt
//curseEraser --input inputfile --dict dictionary.txt
//curseEraser -h or curseEraser --help
//curseEraser -v or curseEraser --version
int main(int argc, char *argv[]){
    //help or version
	if(argc==2){
        if(!strcmp(argv[1],\"-h\") || !strcmp(argv[1],\"--help\")){
            help();
        }else if(!strcmp(argv[1],\"-v\") || !strcmp(argv[1],\"--version\")){
            version();
        }else{
            error(\"Something went wrong...\");
            help();
        }
    //substitute dictionary
    }else if(argc==5){
        if(!strcmp(argv[1],\"-i\") || !strcmp(argv[1],\"--input\")){
            if(!strcmp(argv[3],\"-d\") || !strcmp(argv[3],\"--dict\")){
                FILE * letturaDaEliminare; //puntatore in lettura
                FILE * scritturaDaEliminare; //puntatore in scrittura
                FILE * letturaDizionario; //puntatore in lettura dizionario
                char buffer[BUFFER_DIM];
                char *precWords[WORDS_DIM];
                //apro in lettura il file argv[2]
                letturaDaEliminare  = fopen(argv[2], \"r\");
                //apro in scrittura un file temporaneo
                scritturaDaEliminare = fopen(\"cursedeleter.tmp\", \"w\"); 
                //gestisco errore apertura files:
                 if (letturaDaEliminare == NULL || scritturaDaEliminare == NULL){
                    error(\"\nUnable to open input file.\nPlease check whether file exists and you have read/write privilege.\");
                    exit(EXIT_SUCCESS);
                }
                //se son qui, l'apertura dei file ha avuto successo.
                //Apro il dizionario in lettura:
                letturaDizionario = fopen(argv[4],\"r\");
                if(letturaDizionario == NULL){
                    error(\"\nUnable to open dictionary file.\nPlease check whether file exists and you have read privilege.\");
                    exit(EXIT_SUCCESS);
                }
                //se son qui l'apertura ha avuto successo
                //Metto il dizionario nel mio array di stringhe:
                int k=0;
                int r;
                precWords[k] = malloc(sizeof(char *)*MAXLEN);
                while((r=fscanf(letturaDizionario,\"%[^\n]\n\",precWords[k])) != EOF){
                    k++;
                    precWords[k] = malloc(sizeof(char *)*MAXLEN);
                }
                fclose(letturaDizionario);
                //Dizionario letto, ora posso controllare che non siano presenti quelle parole nel file!
                char newWord[100] = \"CURSEDELETED0\";
                 int j=0;
                //Leggo il programma riga per riga
                while ((fgets(buffer, BUFFER_DIM, letturaDaEliminare)) != NULL){   
                    j++;
                    replaceAll(buffer, precWords, newWord,j,k);
                    fputs(buffer, scritturaDaEliminare);
                }
                fclose(letturaDaEliminare);
                fclose(scritturaDaEliminare);
                remove(argv[2]);
                rename(\"cursedeleter.tmp\", argv[2]);
                printf(\"\nSuccessfully replaced all occurrences with 'CURSEDELETED'!\n\");
            }else{
                error(\"Errore\");
                help();
            }
        }else{
            error(\"Errore\");
            help();
        }
    }
    return 0;
}" >> curseEraser.c;
#creation of errors:
echo " \
//Generic error function
void error(char *s){
    fprintf(stderr,\"%s\n\",s);
    fflush(stderr);
}
" >> error/error.h;

#creation of checks
echo "char *my_itoa(int num, char *str){
	if(str == NULL){
	   return NULL;
	}
	sprintf(str, \"%d\", num);
	return str;
}

//Replace all occurrences of the curse words.
void replaceAll(char *str, char **oldWords, char *newWord, int j,int numCurse){
    char *pos, temp[BUFFER_DIM];
    int index = 0;
    int len;
    char snum[5];
    int indice = 1;
    //Add for
    for(int i=0;i<numCurse;i++){
        len = strlen(oldWords[i]);
        while ((pos = strcasestr(str, oldWords[i])) != NULL){
            strcpy(temp, str);
            fprintf(stdout,\"Found curse word at line: %d\n\",j);
            fflush(stdout);
            index = pos - str;
            str[index] = '\0';
            newWord[12] = my_itoa(indice,snum)[0];
            indice++;
            strcat(str, newWord);
            strcat(str, temp + index + len);
        }
        indice++;
    }
}

void help(){
    fprintf(stdout,\"\nCurseWordEraser v0.3.0\n\n\");
    fprintf(stdout,\"This program allows you to delete all occurrences of curse words within your source code file or normal file. All you have to do is to create a dictionary such as EXAMPLE.txt and then:\n\n\");
    fprintf(stdout,\"curseEraser -i [sourcefile] -d [dictionaryfile] OR curseWord --input [sourcefile] --dict [dictionaryfile]\n\n\");
    fprintf(stdout,\"curseEraser -v OR curseWord --version --> shows you version information about curseEraser\n\n\");
    fflush(stdout);
}
void version(){
    fprintf(stdout,\"CurseWordEraser v0.3.0\nCreated by Taster98 (https://github.com/Taster98/CurseEraser.git)\n\");
    fflush(stdout);
}
" >> src/utils.h;