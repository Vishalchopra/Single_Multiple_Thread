#include<stdio.h>
#include<pthread.h>
#include<fcntl.h>
#include<semaphore.h>
#include<string.h>
#include<stdlib.h>
int fd_thrd;
char *text;
pthread_t thrd[10];
pthread_attr_t tattr;
pthread_mutex_t mutx;
int create_thrd();
void *thrd_opn(void *);
void *thrd_read(void *);
void *thrd_write(void *);
int main()
{
	pthread_mutex_init(&mutx, 0);
	text = (char *)malloc(sizeof(char)*30);
	pthread_create(&thrd[0], &tattr, thrd_opn, NULL);
	sleep(1);
	create_thrd();
}

int create_thrd()
{
	int ret, k;
	static int i = 0;
	char *rept;
	k = 0;
	while(1)
	{
		i++;
		pthread_create(&thrd[i], NULL, thrd_read, (void *) &i);
		sleep(1);
		i++;
		k = i;
		pthread_create(&thrd[k], NULL,thrd_write, (void *)&k);
		sleep(1);
		pthread_join(thrd[k], (void **)&rept);
		printf("%s...........\n", rept);
	}
}
void *thrd_opn(void *arg)
{
	fd_thrd = open("text_thread", O_RDWR| O_CREAT);
	printf("The file discriptor in open:-   %d\n", fd_thrd);
		
}


void *thrd_read(void *arg)
{
	int i, stlen;
	i = *(int *)arg;
	//pthread_mutex_lock(&mutx);	
	printf("Thread %d is running\n",i);
	printf("The file discriptor in read:-   %d\n", fd_thrd);
	printf("Enter the text\n");
	fgets(text, BUFSIZ, stdin);
	//pthread_mutex_unlock(&mutx);	
	pthread_exit("end");
}

void *thrd_write(void *arg)
{
	int i;
	char *ret; 
	i = *(int *)arg;
	pthread_join(thrd[i-1],(void **)&ret);
	//pthread_mutex_lock(&mutx);	
	printf("File Discriptor in thrd_write = %d\n", fd_thrd);
	printf("Thread %d is running\n",i);
	write(fd_thrd, text, strlen(text));
	//pthread_mutex_unlock(&mutx);	
	//close(fd_thrd);
	pthread_exit("bye");

}
