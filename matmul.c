#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h> 
  
int ar[1001];

struct cell{
    int x;
    int y;
};

int a[1001][1001];
int b[1001][1001];
int c[1001][1001];
int n1,m1,n2,m2;

void *myThreadFun(void *vl) 
{ 
    
    struct cell *val=vl;
    c[val->x][val->y]=0;
    for(int i=0;i<m1;i++){
    	c[val->x][val->y]+=(a[val->x][i]*b[i][val->y]);
    }   
    pthread_exit(NULL);
    return NULL; 
} 
   
int main() 
{ 
    printf("Enter values of n and m for first matrix \n");
    scanf("%d %d",&n1,&m1);
    printf("Enter elements\n");

    for(int i=0;i<n1;i++){
        for(int j=0;j<m1;j++){
            scanf("%d",&a[i][j]);
        }
    }

    printf("Enter values of n and m for second matrix \n");
    scanf("%d %d",&n2,&m2);
    printf("Enter elements\n");

    for(int i=0;i<n2;i++){
        for(int j=0;j<m2;j++){ 
            scanf("%d",&b[i][j]);
        }
    }

    clock_t start;		
    start = clock();

    if(m1!=n2){
        printf("Multiplication not possible.\n");
        exit(0);
    }

    pthread_t thread_id[n1][m2];

    for(int i=0;i<n1;i++){
        for(int j=0;j<m2;j++){
            struct cell tmp;
            tmp.x=i;
            tmp.y=j;
            pthread_create(&thread_id[i][j], NULL, myThreadFun, &tmp); 
            pthread_join(thread_id[i][j], NULL);
        }
    }

    printf("All Threads complete in %.4f m secs.\n\nThe resultant matrix is:\n\n",(double) (clock() - start) * 1000 / CLOCKS_PER_SEC);
  
    for(int i=0;i<n1;i++){
        for(int j=0;j<m2;j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }

    return 0;
}
