/**
 * CurseWordEraser: Remove all the unwanted curse words within a source code or any other kind of file!
 */
#define CURSEDELETED2
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_DIM 1000
#define WORDS_DIM 3000
#define MAXLEN 101

#include "./CURSEDELETED1/error.h"
#include "./src/utils.h"

//curseEraser -i inputfile -d dictionary.txt
//curseEraser --input inputfile --dict dictionary.txt
//curseEraser -h or curseEraser --help
//curseEraser -v or curseEraser --version
int main(int argc, char *argv[]){
    //help or version
	if(argc==2){
        if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"--CURSEDELETED3")){
            help();
        }else if(!strcmp(argv[1],"-v") || !strcmp(argv[1],"--version")){
            version();
        }else{
            error("Something went wrong...");
            help();
        }
    //substitute dictionary
    }else if(argc==5){
        if(!strcmp(argv[1],"-i") || !strcmp(argv[1],"--input")){
            if(!strcmp(argv[3],"-d") || !strcmp(argv[3],"--dict")){
                FILE * letturaDaEliminare; //puntatore in lettura
                FILE * scritturaDaEliminare; //puntatore in scrittura
                FILE * letturaDizionario; //puntatore in lettura dizionario
                char buffer[BUFFER_DIM];
                char *precWords[WORDS_DIM];
                //apro in lettura il file argv[2]
                letturaDaEliminare  = fopen(argv[2], "r");
                //apro in scrittura un file temporaneo
                scritturaDaEliminare = fopen("cursedeleter.tmp", "w"); 
                //gestisco errore apertura files:
                 if (letturaDaEliminare == NULL || scritturaDaEliminare == NULL){
                    error("\nUnable to open input file.\nPlease check whether file exists and you have read/write privilege.");
                    exit(EXIT_SUCCESS);
                }
                //se son qui, l'apertura dei file ha avuto successo.
                //Apro il dizionario in lettura:
                letturaDizionario = fopen(argv[4],"r");
                if(letturaDizionario == NULL){
                    error("\nUnable to open dictionary file.\nPlease check whether file exists and you have read privilege.");
                    exit(EXIT_SUCCESS);
                }
                //se son qui l'apertura ha avuto successo
                //Metto il dizionario nel mio array di stringhe:
                int k=0;
                int r;
                precWords[k] = malloc(sizeof(char *)*MAXLEN);
                while((r=fscanf(letturaDizionario,"%[^\n]\n",precWords[k])) != EOF){
                    k++;
                    precWords[k] = malloc(sizeof(char *)*MAXLEN);
                }
                fclose(letturaDizionario);
                //Dizionario letto, ora posso controllare che non siano presenti quelle parole nel file!
                char newWord[100] = "CURSEDELETED0";
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
                rename("cursedeleter.tmp", argv[2]);
                printf("\nSuccessfully replaced all occurrences with 'CURSEDELETED'!\n");
            }else{
                error("Errore");
                help();
            }
        }else{
            error("Errore");
            help();
        }
    }
    return 0;
}
