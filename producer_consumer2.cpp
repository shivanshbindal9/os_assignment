#include <semaphore.h> 
// #include <thread>
// #include <mutex>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int BUFFER_SIZE  =  100;
sem_t empty,full;
int max_run = 20;
int item_no = 0;
pthread_mutex_t mutex;
void *producer(void *args){
	while(max_run>0){
	sem_wait(&empty);
	pthread_mutex_lock(&mutex);
	item_no += 1;
	cout<<"The producer produced item_no : " << item_no<<"\n";
	max_run -= 1;
	pthread_mutex_unlock(&mutex);
	sem_post(&full);
}
}
void *consumer(void *args){
	while(max_run>0){
	sem_wait(&full);
	pthread_mutex_lock(&mutex);
	cout<<"The consumer consumed item_no : " << item_no << "\n";
	item_no -= 1;
	max_run -= 1;
	pthread_mutex_unlock(&mutex);
	sem_post(&empty);
}
}

int main(){
	pthread_t produce, consume;
	sem_init(&empty,0,BUFFER_SIZE);
	sem_init(&full,0,0);
	cout<<"This is implementation of producer consumer problem using semaphores \n";
	pthread_mutex_init(&mutex,NULL);
	pthread_create(&produce,NULL,producer,NULL);
	pthread_create(&consume,NULL,consumer,NULL);
	pthread_exit(NULL);
}