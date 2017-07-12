/**************Header Files****************/

#include <stdio.h>
#include <pthread.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*******************Global Variable**************/
int fd;
char text[10];
char buff[BUFSIZ];
pthread_t thrd[2];
pthread_attr_t tattr;

/*****************Function Prototype****************/
void open_func();
void thread_func();
void *thread_read(void *);
void *thread_write(void *);

int main()
{
	open_func();		//Function to open file
	thread_func();		//Function to create thread
	while(1){
		memset(text, '\0', sizeof(text));
		printf("Wanna Read or Write to file OR exit to end\n");
		fgets(text, BUFSIZ, stdin);
		//scanf("%m[a-z]", &text);
		//scanf("%s", text);
		if(strncmp(text, "exit", 4) == 0)
			break;
		printf("%s\n", text);
		//sleep(1);
	}
	
	close(fd);


	return 0;

}

void open_func()
{
	fd = open("development_file.txt", O_RDWR | O_CREAT);
	if(fd == -1){
		perror("open");
		exit(EXIT_FAILURE);
	}
}

void thread_func()
{
	int i = 0;
	if(pthread_attr_init(&tattr)){
		perror("pthread_attr_init");
		exit(EXIT_FAILURE);
	}

	if(pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED)){
		perror("pthread_attr_setdetachstate");
		exit(EXIT_FAILURE);
	}
	
	pthread_create(&thrd[0], &tattr, &thread_read, (void *)&i);
	i++;
	pthread_create(&thrd[1], &tattr, &thread_write, (void *)&i);
}

void *thread_read(void *num)
{
	int i = *(int *)num;
	int bytes, val;
	while(1){
		if(strncmp("read", text, 4) == 0){
			printf("i'm in the read thread\n");
			memset(buff , '\0', BUFSIZ);
			lseek(fd, 0, SEEK_SET);
			bytes = read(fd, buff, sizeof(buff));
			printf("Number of byte read = %d\n", bytes);
			for(val = 0; val < sizeof(sizeof(buff)); ++val)
				printf("%c :\n", buff[val]);
			memset(text , '\0', BUFSIZ);
		}
		//free(text);
	}
}

void *thread_write(void *num)
{
	int i = *(int *)num;
	int bytes;
	while(1){
		if(strncmp("write", text, 5) == 0){
			printf("I'm in write thread.\n What you wanna write\n");
			fgets(buff, sizeof(buff), stdin);
			bytes = write(fd, buff, sizeof(buff));
			printf("%d number of bytes written\n", bytes);
			memset(text , '\0', BUFSIZ);

		}
	}
}
