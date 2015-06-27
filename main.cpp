#include <iostream>
#include <sys/time.h>
#include "array.h"

using namespace std;

double test(void (*f)())
{
    timeval start,end;
    gettimeofday(&start,NULL);
    f();
    gettimeofday(&end,NULL);
    return (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec)/1000000.0;
}

Array<int> array;

const int times = 10000000;

void run(){
    int time = times * 6;
    while(time--) {
        array.append(time);
    }
}

int main()
{
    // append 60000000 items need time
    // about 13.6958s

    cout <<
            test( run )
         << "s" << endl;

    int index(0);

    while(1){
        cout << "input the index to accese :" ;
        cin >> index ;
        cout << endl;
        cout << "array[ "<< index << "] :" << array[index] << endl;
    }

    return 0;
}


