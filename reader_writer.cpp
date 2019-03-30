#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int write_read = 1;
int readerno = 0;
int max_run = 20;
int mut = 1;
mutex m;
void sem_wait(string s)
{
		while (write_read == 0);
		write_read--;
		
}

void sem_signal(string s)
{
		write_read++;
}
void writer(){
	while(max_run > 0){
		sem_wait("empty");
		cout<<"Writer is writing files\n";
		max_run--;
		sem_signal("full");
	}
}

void reader(){
	while(max_run > 0){
		m.lock();
		readerno++;
		if(readerno == 1)
			sem_wait("wrt");
		m.unlock();
		cout<<"Reader is reading\n";
		m.lock();
		readerno--;
		if(readerno == 0)
			sem_signal("full");
		m.unlock();
		max_run--;
	}
}

int main(){
	cout<<"This is implementation of reader writer problem using semaphores \n";
	thread t1(writer);
	thread t2(reader);
	t1.join();
	t2.join();
	return 0;
}