#include <stdio.h>
#include <stdlib.h>


int main(){

  void *v = malloc(9000000000000000000);

  if(v == NULL){
    printf("\nNo se pudo asignar memoria\n");
  }
  else{
    printf("\nSi se pudo asignar memoria\n");
  }
  free(v);
}
