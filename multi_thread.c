#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<fcntl.h>
#include<semaphore.h>
#include<string.h>

int create_thrd();
void *thrd_opn(void *);
void *thrd_read(void *);
void *thrd_write(void *);

pthread_t thrd[10];
pthread_attr_t tattr;
int fd_thrd;
sem_t sem_thrd;
char *text;
int main()
{
	sem_init(&sem_thrd, 0, 1);
	text = (char *)malloc(sizeof(char)*1000);
	//create_thrd();
//}

//int create_thrd()
//{
	int ret, k;
	static int i = 0;
	char *rept;
	k = 0;
	//ret = pthread_attr_init(&tattr);
	//ret = pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	pthread_create(&thrd[i], NULL, thrd_opn, (void *)& i);
	while(1)
	{
		if(strncmp(text, "exit", 4)==0)
			break;
		if(i > 0)
		printf("File discriptor after the while :-    %d ....%d\n", fd_thrd, i);
		/*if(i == 0)
		{
			//pthread_create(&thrd[i], &tattr, thrd_opn, (void *)& i);
			pthread_create(&thrd[i], NULL, thrd_opn, (void *)& i);
			sleep(1);
		}*/
		i++;
		//pthread_create(&thrd[i], &tattr, thrd_read, (void *) &i);
		pthread_create(&thrd[i], NULL, thrd_read, (void *) &i);
		//pthread_join(thrd[i], (void **)&rept);
		
		//sleep(2);
		i++;
		k = i;
		if(pthread_create(&thrd[k], NULL, thrd_write, (void *)&i) != 0)
			perror("pthread_create\n");
		//sleep(1);
		pthread_join(thrd[k], (void **)&rept);
		//close(fd_thrd);
		printf("%s...........\n", rept);
	}
	sem_destroy(&sem_thrd);
}
void *thrd_opn(void *arg)
{
	int i, temp;
	i = *(int *)arg;
	fd_thrd = open("text.thread", O_RDWR| O_CREAT);
	//sem_wait(&sem_thrd);	
	printf("The file discriptor in open:-   %d\n", fd_thrd);
	//sem_post(&sem_thrd);
}


void *thrd_read(void *arg)
{
	int i, stlen;
	i = *(int *)arg;
	sem_wait(&sem_thrd);	
	printf("The file discriptor in read:-   %d\n", fd_thrd);
	printf("Enter the text\n");
	fgets(text, BUFSIZ, stdin);
	printf("%s  %d  in the read\n", __func__, strlen(text));
	sem_post(&sem_thrd);
	pthread_exit("bye");
}

void *thrd_write(void *arg)
{
	sleep(1);
	int i;
	i = *(int *)arg;
	char a = 'a';
	sem_wait(&sem_thrd);	
	printf("File Discriptor in thrd_write = %d\n", fd_thrd);
	write(fd_thrd, text, strlen(text));
	sem_post(&sem_thrd);
	pthread_exit("bye");

}
