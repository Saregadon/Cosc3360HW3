#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <pthread.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <stdio.h>

using namespace std;

const int NMAX = 30; //name Max
static int nCustomers, nHadToWait, nVacced, nFreeNurses;
static pthread_mutex_t customer_lock;

struct Arguments
{
    string cname;
    int elapsedtime = 0;
    int waittime = 0;
    int safetyprecaution = 0;
    int nThreads = 0;
    Arguments *next = nullptr;
};

void *customer(void *arg)
{
    //struct Arguments *argptr;
    //char myName[NMAX];
    int myVTime, myRTime;
    int hasWaited = 0;
    Arguments* argptr = (Arguments *) arg;
    //strcpy(myName, argptr->cname);
    myVTime = argptr->waittime; //wait time for getting into get vaccinated
    myRTime = argptr->safetyprecaution; //time to wait after the customer has the shot
    cout << argptr->cname << " arrives at the center." << endl;

    if(pthread_mutex_trylock(&customer_lock) != 0)
    {
        cout << argptr->cname << " has to wait." << endl;
        pthread_mutex_lock(&customer_lock);
        nHadToWait++;
        nFreeNurses--; //if customers != 0, has to wait so a nurse is also taken up
    }

    if(nFreeNurses > 0) //allows the pthread to unlock
    {
        pthread_mutex_unlock(&customer_lock);
    }

    cout << argptr->cname << " is getting the vaccine." << endl;
    sleep(myVTime);
    nVacced++;
    cout << argptr->cname << " got vaccinated." << endl;

    pthread_mutex_lock(&customer_lock);
    if(nFreeNurses == 0)
    {
        //wait on condition
        pthread_mutex_unlock(&customer_lock);
    }
    //update counters and print customer is getting jab
    pthread_mutex_unlock(&customer_lock);
    sleep(myVTime);
    pthread_mutex_lock(&customer_lock);
        //update counters and print customer got vaccinated
        //signal condition
    pthread_mutex_unlock(&customer_lock);
}

int main()
{
    //ifstream input;
    Arguments argList;
    pthread_t tid;

    //pthread_create(&tid,NULL,customer,(void*)custData);

    pthread_join(tid, NULL);

    int nThreads = 0;

    while(cin >> argList.cname >> argList.elapsedtime >> argList.waittime >> argList.safetyprecaution)
    {
        sleep(argList.elapsedtime);
        char testname = (char)argList.cname;
        strcpy(argList.cname.c_str(), name);
        pthread_create(&tid[argList.nThreads], NULL, customer, (void *) &argList);
        argList.nThreads++;
    }

    return 0;
}