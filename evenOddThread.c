#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void funcCreateThread();
void *evenThread(void *);
void *oddThread(void *);
int evenOddThread(int);
int count;

#define MAXCOUNT 200
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

int main ()
{
	funcCreateThread();
	while(1);
	return 0;
}

void funcCreateThread()
{
	pthread_t pthreadId[2];
	pthread_attr_t attr;
	if (pthread_attr_init(&attr)){
		perror("pthread_attr_init");
		exit(EXIT_FAILURE);
	}
	//mutex_init(&mutex);
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED)){
		perror("pthread_attr_setdetachedstate");
		exit(EXIT_FAILURE);
	}
	pthread_create(&pthreadId[0], &attr, &evenThread, (void *)&pthreadId[0]);
	pthread_create(&pthreadId[1], &attr, &oddThread, (void *)&pthreadId[1]);
}

void *evenThread(void *data)
{
	printf("in Even Thread\n");
	int i, result;
	for (;;){
		/*pthread_mutex_lock(&mutex);
		pthread_cond_wait(&condition_var, &mutex);
		result = evenOddFunc(i);
		if(result)
			printf("Number is even %d\n", i);
		pthread_cond_signal(&condition_var);
		pthread_mutex_unlock(&mutex);	*/
		pthread_mutex_lock(&mutex);
		if ( (count & 1) == 0 )
			pthread_cond_wait(&condition_var, &mutex);
		count ++;
		printf("Number is even %d\n", count);
		pthread_cond_signal(&condition_var);
		if (count >= MAXCOUNT){
			pthread_mutex_unlock(&mutex);	
			return (NULL);
		}
		pthread_mutex_unlock(&mutex);	
		//pthread_cond_signal(&condition_var);
	}

}

void *oddThread(void *data)
{
	printf("in Odd Thread\n");
	int i, result;
	for (; ;){
		pthread_mutex_lock(&mutex);
		if ( (count & 1) != 0 )
			pthread_cond_wait(&condition_var, &mutex);
		count ++;
		printf("Number is odd %d\n", count);
		pthread_cond_signal(&condition_var);
		if (count >= MAXCOUNT){
			pthread_mutex_unlock(&mutex);	
			return (NULL);
		}
		/*pthread_cond_signal(&condition_var);
		result = evenOddFunc(i);
		if(!result)
			printf("Number is odd %d\n", i);*/
		pthread_mutex_unlock(&mutex);	
	}
}

int evenOddFunc(int data)
{
	if ((data & 1) == 0)
		return 1;
	else 
		return 0;
}
