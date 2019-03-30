#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

int max_run = 20;
int free_seats = 10;
int custno = 0;
int barberno = 1;
mutex m;
void sem_wait_barber(){
	while(custno<=0);	
}
void sem_signal_barber(){
	custno--;
	if(custno==0)
		cout<<"barber goes to sleep\n";
}
void sem_signal_customer(){
	custno++;
	if(custno==1)
		cout<<"wake up the barber\n";
}
void barber(){
	while(max_run>0){
		sem_wait_barber();
		m.lock();
		free_seats++;
		cout<<"barber is cutting hair\n";
		sem_signal_barber();
		m.unlock();
		max_run--;
	}
}
void customer(){
	while(max_run>0){
		m.lock();
		if(free_seats>0){
			free_seats--;
			cout<<"new customer entered no:" << custno+1<<"\n";
			sem_signal_customer();
			m.unlock();
		}
		else{
			cout<<"Seats are full"<<"\n";
		m.unlock();
	}
		max_run--;
	}
}

int main(){
	cout<<"This is implementation of sleeping barber problem using semaphores \n";
	thread t1(customer);
	thread t2(barber);
	t1.join();
	t2.join();
	return 0;
}