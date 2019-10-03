#include <iostream>
#include <thread>

using namespace std;

int BUFFER_SIZE  =  100;
int item_no = 0;
int max_run = 20;

class CustomMux
{ 
    std::atomic<int> m; 
public:
    CustomMux(): m(0) {} 
    void lock() 
    { 
      while ((m++) > 1) m--;
    } 
    void unlock() 
    { 
        m--;
    } 
};

class semaphore {
private:
  CustomMux m;
  atomic<int> s;
public:
  semaphore(int init = 1): s(init) {}
  void Wait() {
    while (true) {
      while (s <= 0);
      m.lock();
      if (s <= 0) { m.unlock(); continue; }
      s--;
      m.unlock();
      break;
    }
  }
  void Signal() { s++; }
};


CustomMux m;
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