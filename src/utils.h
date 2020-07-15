char *my_itoa(int num, char *str){
	if(str == NULL){
	   return NULL;
	}
	sprintf(str, "%d", num);
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
            fprintf(stdout,"Found curse word at line: %d\n",j);
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
    fprintf(stdout,"\nCurseWordEraser v0.3.0\n\n");
    fprintf(stdout,"This program allows you to delete all occurrences of curse words within your source code file or normal file. All you have to do is to create a dictionary such as EXAMPLE.txt and then:\n\n");
    fprintf(stdout,"curseEraser -i [sourcefile] -d [dictionaryfile] OR curseWord --input [sourcefile] --dict [dictionaryfile]\n\n");
    fprintf(stdout,"curseEraser -v OR curseWord --version --> shows you version information about curseEraser\n\n");
    fflush(stdout);
}
void version(){
    fprintf(stdout,"CurseWordEraser v0.3.0\nCreated by Taster98 (https://github.com/Taster98/CurseEraser.git)\n");
    fflush(stdout);
}

