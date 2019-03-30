#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int BUFFER_SIZE  =  100;
int item_no = 0;
int max_run = 20;
mutex m;
int turn = 0;
int mut = 1;
void sem_wait(string s)
{
	if(s == "empty")
	{
		while(item_no == BUFFER_SIZE);
		mut--;
	}
	else{
		while (item_no == 0);
		mut--;
	}
}
void sem_signal(string s)
{
	if(s == "empty")
	{
		mut++;
	}
	else{
		mut++;
	}
}
void producer(){
	while(max_run>0){
	sem_wait("empty");
	m.lock();
	item_no += 1;
	cout<<"The producer produced item_no : " << item_no<<"\n";
	max_run -= 1;
	m.unlock();
	sem_signal("full");
}
}
void consumer(){
	while(max_run>0){
	sem_wait("full");
	m.lock();
	cout<<"The consumer consumed item_no : " << item_no << "\n";
	item_no -= 1;
	max_run -= 1;
	m.unlock();
	sem_signal("empty");
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