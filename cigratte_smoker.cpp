#include <iostream>
#include <thread>
#include <mutex>
#include <random>

using namespace std;
int val = 0;
int max_run = 20;
mutex m;
int res = 0;
void sem_wait_agent()
{
	while(val!=0);
}
void sem_signal_agent(int x)
{
	val = x;
	//cout<<val<<endl;
}
void sem_signal_smoker()
{
	val= 0;
}
void sem_wait_smoker(int x)
{
	while(val!=x&&max_run>0);
	res = x;
}
void agent(){
	while(max_run>0){
	sem_wait_agent();
	m.lock();
	int random = rand();
	random = random%3 +1;
	if( random == 1){
		cout<<"Agent produced item 1\n";
		sem_signal_agent(1);
	}
	else if( random == 2 ){
		cout<<"Agent produced item 2\n";
		sem_signal_agent(2);
	}
	else if( random == 3){
		cout<<"Agent produced item 3\n";
		sem_signal_agent(3);}
	m.unlock();
	max_run--;
}
}

void smoker(int s){
	while(max_run>0){
	sem_wait_smoker(s);
	if(max_run<=0)
		break;
	m.lock();
	cout<<"Cigratte was smoked by smoker"<<s<<"\n";
	sem_signal_smoker();
	m.unlock();
	max_run--;
}
}

int main()
{
	srand(clock());
	cout<<"This is implementation of cigratte smoker problem using semaphores \n";
	thread t1(agent);
	thread t2(smoker,1);
	thread t3(smoker,2);
	thread t4(smoker,3);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	return 0;
}