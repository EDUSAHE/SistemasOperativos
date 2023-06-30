#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

FILE *abrirTuberia( char *nombreTuberia, char *modo ){
   int error, errorFifo;
   struct stat infoTuberia;
   FILE *fp = NULL;
   error = stat(nombreTuberia, &infoTuberia);
   if( error == 0){ // verificar que se trata de una tuberia
      if( S_ISFIFO( infoTuberia.st_mode ) )
	 fp = fopen(nombreTuberia, modo);
   }
   else{
      errorFifo = mkfifo(nombreTuberia, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH  );
      if( errorFifo == 0)
	 fp = fopen(nombreTuberia, modo);
   }
   return fp;
}