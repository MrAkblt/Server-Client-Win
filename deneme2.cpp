#include <iostream>
#include <pthread.h>
#include <windows.h>
#include <vector>
using namespace std;

vector<int> numbers;
void *sendhost(){
    Sleep(3000);
    while(true){
        if(!numbers.empty()){
        cout<<numbers.front()<<endl;
        numbers.erase(numbers.begin());
        Sleep(300);
        }
    }
}
void *startcounter(){
    int i=0;
    while(true){
        numbers.push_back(i);
        Sleep(1000);
        i++;
    }
}
main(){
    pthread_t sc, sh;
    pthread_create(&sc,NULL,startcounter,NULL);
    pthread_create(&sh,NULL,sendhost,NULL);
    pthread_join(&sc,NULL);
    pthread_join(&sh,NULL);
    /*thread t1(startcounter);
    thread t2(sendhost);
    t1.join();
    t2.join();*/


}
