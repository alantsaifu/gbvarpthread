/*
 * gbvarpthread.c
 * This example creat a pthread shared a global variable.
 */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#define MAX 15

pthread_t thread[2];
pthread_mutex_t mut;
int number;
int i;
void *thread1()
{
  pthread_detach(pthread_self());	
	printf ("pthread1 : I'm thread 1\n"); 
	for (i = 0; i < MAX; i++)
	{
		pthread_mutex_lock(&mut);
		number++;
      		printf("pthread1 : number = %d\n",number);
		pthread_mutex_unlock(&mut);
    		usleep(1);
	}
	printf("pthread1 : done the thread\n");
  	pthread_exit(NULL);
}
void *thread2()
{
  pthread_detach(pthread_self());
	printf("pthread2 : I'm thread 2\n"); 
	for (i = 0; i < MAX; i++)
	{
		pthread_mutex_lock(&mut);
		number++;
      		printf("pthread2 : number = %d\n",number);
		pthread_mutex_unlock(&mut);
    		usleep(1);
	}
	printf("pthread2 : done the thread\n");
	pthread_exit(NULL);
}
void thread_create(void)
{
	int temp;
	memset(&thread, 0, sizeof(thread));
	/*create thread*/
	if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0){
		printf("create pthread 1 failed!\n");
	}
	else{
		printf("create pthread 1 done\n");
	}
	if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0){	
		printf("create pthread 2 failed");
	}
	else{
		printf("create pthread 2 done\n");
	}
}

int main()
{
	number=0;
    	/*mutex init*/
    	pthread_mutex_init(&mut,NULL);
    	printf("I'm the main process, do the thread_create\n");
    	thread_create();
    	printf("I'm the main process, do the thread_wait\n");
    	while(1);
    	return 0;
}

