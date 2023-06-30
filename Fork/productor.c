#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/*  productor */

FILE *abrirTuberia(char *, char *);

int main(){
   char cadena[256];
   FILE *fp = abrirTuberia("pipeta", "w");
  
   if( fp == NULL )
      fprintf(stderr, "la pipeta no abre\n");
   else while(1){
	 fprintf(stdout, "introduce una cadena");
	 fgets( cadena, 128, stdin);
	 fputs( cadena, fp );
	 if(strcmp(cadena, "exit\n") == 0)
	   fclose(fp);
   }
   return 0;
}


