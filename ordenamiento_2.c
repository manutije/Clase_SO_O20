//Bibliotecas

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <math.h>
 //---------------------------------------------------------------------------------------------------
 // Declaracion estructura de limites
 struct limit_values{
   int lower;
   int upper;
   int hilo;
 };

//Variable global para almacenar el arreglo
int *arreglo;

//Declaracion de la funcion para ordenar
void* order(void *param) ;

//----------------------------------------------------------------------------------------------------
//Funciones para encontrar CPUS

int get_ncpus() {
	// Return processors available
	return get_nprocs();
}


//------------MAIN---------------------------------------------------------------------------
int main(){

  //Declaracion de variables
  int i;
  time_t t;
  pthread_t tid[8]; //Arreglo de 8 porque es el numero maximo de CPus en mi compu
	pthread_attr_t attr[8];
  int num_ale = 0;
  int num_cores = 9;
  int cores_disp = 0;
  int lim;
  int lim_inf;
  struct limit_values limits[8];
  int cont = 0;
  int temp = 0;
  clock_t t1, t2;

  //Preguntar cuantos numeros desea ordenar
  printf("Cuantos numeros aleatorios deseas ordenar: ");
  scanf("%d",&num_ale);

  //Encontrar cores disponibles
  cores_disp =get_ncpus ();

  //Imprimir cores disponibles y preguntar cuantos se desean usar
  while(num_cores>cores_disp){
  printf("Se encontraron %d cores. Cuantos quieres usar: ",cores_disp);
  scanf("%d",&num_cores);
  if(num_cores >cores_disp){
    printf ("\n\nERROR SOLO TIENES %d CORES DISPONIBLES\n\n",cores_disp);
  }
  };

  //Llenar el arreglo con numeros aleatorios
  srand((unsigned) time(&t));
  arreglo =(int*) malloc(num_ale* sizeof(int));
  for(i=0;i<num_ale;i++){
    arreglo[i]=rand()%10000;
    printf("%d\n",arreglo[i]);
  }

  /*El limite es el parametro que recibo*/
	lim = num_ale;
  printf ("Limite: %d\n",lim);

   //Si la division da exacto
  lim_inf =(lim/num_cores);


  //Si la division no da exacto
  if((lim%num_cores)!=0){
    printf ("No da exacto \n");
    lim_inf = (lim/num_cores);
    lim_inf = lim_inf+1;
  }

  printf ("Numeros por hilo: %d\n",lim_inf);

  temp = lim_inf;
  for(int j=0;j<num_cores;j++){
    limits[j].lower = cont;
    limits[j].upper = lim_inf-1;
    limits[j].hilo = j;
    cont =lim_inf;
    lim_inf= lim_inf + temp;
    if(j==(num_cores-1)){
      limits[j].upper=lim-1;
    }
  }

  //Iniciar cronometro
  t1 = clock();
  //Crear los threads
  for(int i = 0;i<num_cores;i++){
    pthread_attr_init(&attr[i]);
	  pthread_create(&tid[i], &attr[i], order, &limits[i]);
    pthread_join(tid[i], NULL);
  }

  //parar cronometro
  t2 = clock();
  printf("\n\n\n\n Tiempo que se tardo en ejecutar: %.5f\n",(t2 - t1) /(double)CLOCKS_PER_SEC);
}


//-------------------------------------------------------------------------------------------------------
void* order(void *param) {
    struct limit_values *par = (struct limit_values*)param;
    int lower = par->lower;
    int upper = par->upper;
    int hilo = par->hilo;
    int temp = 0;

    printf("\n\n\nEl lower de este hilo es: %d\n",lower);
    printf("El upper de este hilo es: %d\n",upper);
    //Ordenador por metodo de burbuja
    for (int i = lower; i <=upper ;i++)
      {
        for (int j = lower; j<upper ; j++)
          {
            if(arreglo[i]<arreglo[j]){
              temp = arreglo[j];
              arreglo[j] = arreglo[i];
              arreglo[i] = temp;
            }
          }
      }

  printf ("Los valores arreglados en el hilo %d son:\n",hilo);
  for(int k = lower;k<=upper;k++){
    printf("Valor %d: %d\n",k,arreglo[k]);
  }
	pthread_exit(0);
}
