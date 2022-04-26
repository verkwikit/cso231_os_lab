#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
int n;                          // size of fibonacci sequence.
int *fibseq;   // arry holds the value of each fibonacci term.
pthread_t t1;

void *mythread_function(void *args)
{
    int n1 = 0, n2 = 1, n3, i;
    fibseq[0] = 0;
    fibseq[1] = 1;
    
    //printf("\n %d %d", n1, n2);   
    for (i = 2; i < n; i++) 
    {
        n3 = n1 + n2;
        //printf(" %d", n3);
        fibseq[i] = n3;
        n1 = n2;
        n2 = n3;
    }

}

int main()
{
    printf("enter the number of elements ");
    scanf("%d", &n);
    fibseq  = (int *)malloc(n * sizeof(int));
  
    pthread_create(&t1, NULL, mythread_function, (void*)&n);
    pthread_join(t1, NULL);
    
    int j;
    for (j = 0; j < n; j++)
    {
        printf("%d ", fibseq[j]);
    }
    printf("\n");

    return 0;
}