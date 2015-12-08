#include<stdio.h>
#include<pthread.h>
int flag ;

void * func(void *);
int main()
{
	flag = 1;
	pthread_t thrd;
	int a = 5;
	pthread_create(&thrd, NULL, &func, &a);
	while(flag);
	printf("After the termination of the thread\n");
	return 0;
}


void * func(void *p)
{
	int *a = (int *)p;	
	printf("%s  %d\n", __func__, *a);
	//sleep(5);
	flag = 0;
}
