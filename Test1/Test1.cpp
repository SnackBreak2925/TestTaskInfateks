#include <iostream>
#ifdef _WIN32
#include <thread>
#else
#include<pthread.h>
#endif
#include "container.h"
#include "client.h"
using namespace std;

//5612344810848792301610846870685403487484163416850980584789631416
//9999999999999999999999999999999999999999999999999999999999999999
#ifdef _WIN32
int thread1(container& a)
{
	a.core_thr1();
	return 0;
}

int thread2(container& a)
{
	a.core_thr2();
	return 0;
}
#else
void* thread1(void* b)
{
	container* a = (container*) b;
	a->core_thr1();
	return 0;
}

void* thread2(void* b)
{
	container* a = (container*) b;
	a->core_thr2();
	return 0;
}
#endif

int main()
{
	cout << "Input 64-digit string" << endl << "Input exit or 0 for exit" << endl;
	while(1)
	{
		container a;
#ifdef _WIN32
		thread thr1(thread1, ref(a));
		thread thr2(thread2, ref(a));
		thr1.join();
		thr2.join();
#else
		pthread_t thr1;
		pthread_t thr2;
		pthread_attr_t atr1;
		pthread_attr_t atr2;
		pthread_attr_init(&atr1);
		pthread_attr_init(&atr2);
		pthread_create(&thr1, &atr1, &thread1, (void*)&a);
		pthread_create(&thr2, &atr2, &thread2, (void*)&a);
		pthread_join(thr1, NULL);
		pthread_join(thr2, NULL);
#endif
	}
	return 0;
}