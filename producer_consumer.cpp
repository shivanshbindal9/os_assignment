#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int BUFFER_SIZE  =  100;
int item_no = 0;
int max_run = 20;
mutex m;
int turn = 0;
void producer(){
	while(max_run>0){
	m.lock();
	if(item_no == 100)
	{
		cout<<"Buffer is full\n";
	}
	else{
	item_no += 1;
	cout<<"The producer produced item_no : " << item_no<<"\n";
	}
	max_run -= 1;
	m.unlock();
}
}
void consumer(){
	while(max_run>0){
	m.lock();
	if(item_no == 0)
	{
		cout<<"Buffer is empty\n";
	}
	else{
	cout<<"The consumer consumed item_no : " << item_no << "\n";
	item_no -= 1;
}
	max_run -= 1;
	m.unlock();
}
}
int main()
{
	cout<<"This is implementation of producer consumer problem using semaphores \n";
	thread t1(producer);
	thread t2(consumer);
	t1.join();
	t2.join();
	return 0;
}