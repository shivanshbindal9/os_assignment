#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;

int max_run = 20;
int n = 5;
int st[5] = {};
mutex m;
void sem_wait_phil(int x){
	while(st[(x+1)%5]==1||st[(x)%5]==1);
}
void sem_signal_eat(int x){
	st[(x+1)%5] = 1;
		st[x] = 1;
}
void sem_signal_release(int x){
	st[(x+1)%5] = 0;
		st[x] = 0;
}
void philosopher(int x){
	while(max_run>0){
		m.lock();
		cout<<"Philosopher "<<x+1<<" wishes to eat\n";
		m.unlock();
		sem_wait_phil(x);
		m.lock();
		sem_signal_eat(x);
		cout<<"Philosopher "<<x+1<<" is eating \n";
		m.unlock();
		m.lock();
		sem_signal_release(x);
		cout<<"Philosopher "<<x+1<<" has now eaten and is thinking\n";
		m.unlock();
		max_run--;
	}

}
int main(){
	cout<<"This is implementation of dining philosopher problem using semaphores \n";
	thread t1(philosopher,0);
	thread t2(philosopher,1);
	thread t3(philosopher,2);
	thread t4(philosopher,3);
	thread t5(philosopher,4);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	return 0;
}