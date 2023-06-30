#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/* consumidor */

FILE *abrirTuberia(char *, char *);

int main(){
   char buffer[1024];
  FILE *fp = abrirTuberia("pipeta", "r");
   if( fp == NULL )
      fprintf(stderr, "la pipeta no abre\n");
   else
      while( !feof( fp ) ){
	 fgets(buffer, 128, fp );
	 fputs(buffer, stdout);
      }
   fclose(fp);
   return 0;
}




