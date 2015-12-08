#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>

void *sig_han(int sig)
{
	printf("The thread is terminated\n");
	pthread_exit("thread is exit");
	
}
thrd_func(void *);
int main()
{
	int res, i, n;
	pthread_t thrd[10];
	char *thr;
	signal(SIGINT, sig_han);
	for(i = 0; i < 3; i++)
	{
		res = pthread_create( &thrd[i], NULL, &thrd_func, i);	
		if(res == -1)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		printf("%d thread is created\n", i);
		sleep(1);
	}
	for(i = 0; i < 3; i++)
	{
		printf("Enter the thread number to be ended:-\n");
		scanf("%d", &n);
		pthread_kill(thrd[n], 2);
		pthread_join(thrd[n],  &thr);	
		printf("Return from the %d thread %s\n", i, thr);	
	}
	return 0;
}

thrd_func( void *arg)
{
	int i;
	i = (int *)arg;
	signal(SIGINT, sig_han);
	while(1)
	{
		printf("%d numbered thread is running\n", i);
		sleep(3);
	}
}

