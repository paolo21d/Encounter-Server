/*

#include "semafor.h"
#include <thread>
#include <iostream>

using namespace std;

Semaphore sem1(0);
Semaphore sem2(0);

void a(int x)
{
    cout << "a " << x << endl;
    if(x){
        sleep(3);
    }
}

void b(int x)
{
    cout << "b " << x << endl;
    if(x){
        sleep(3);
    }
}

void x(int y)
{
    a(y);

    if(y){
		sem1.p();
		sem2.v();
	}
	else {
		sem1.v();
		sem2.p();
	}

    b(y);
}

int main()
{
    thread onz(x, 0);
    thread diex(x, 1);

    onz.join();
    diex.join();
}

*/