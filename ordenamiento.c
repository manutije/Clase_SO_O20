#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int *arreglo;
void* order(void *param) ;

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char *argv[]){

    int i;
    time_t t;
    pthread_t tid, tid2; /* the thread identifier */
	pthread_attr_t attr, attr2; /* set of attributes for the thread */

	if (argc != 2) {
		fprintf(stderr, "usage: a.out <integer value>\n");
		/*exit(1);*/
		return -1;
	}
	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "Argument %d must be non-negative\n", atoi(argv[1]));
		/*exit(1);*/
		return -1;
	}

    srand((unsigned) time(&t));
    arreglo =(int*) malloc(atoi(argv[1])* sizeof(int));
    for(i=0;i<atoi(argv[1]);i++){
        arreglo[i]=rand()%100;
        printf("%d\n",arreglo[i]);
    }

    /*El limite es el parametro que recibo*/
	int lim = atoi(argv[1]);
    int lim1[]= {0,(lim/2)-1};
    int lim2[]= {lim/2,lim-1};
	/* get the default attributes */
	pthread_attr_init(&attr);
	/* get the default attributes */
	pthread_attr_init(&attr2);

	/* create the thread */
	pthread_create(&tid, &attr, order, lim1);

	/* create the thread */
	pthread_create(&tid2, &attr2, order, lim2);

	/* now wait for the thread to exit */
	pthread_join(tid2, NULL);
}

void* order(void *param) {
    int *par = (int *)param;
    int lower = par[0];
    int upper = par[1];
    int nitems = upper - lower;
    int values[nitems];
    int j= 0;

    for (int i = lower; i<=upper;i++)
    {

        values[j]=arreglo[i];
        j++;
    }

	qsort(values, nitems+1, sizeof(int), cmpfunc);
	printf("Elementos ordenados\n");
	for(int k = 0;k<=nitems;k++){
        printf("%d\n",values[k]);
	}
	pthread_exit(0);
}
