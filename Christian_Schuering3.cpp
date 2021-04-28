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

struct Arguments
{
    string cname;
    Arguments* next = nullptr;
};

struct cust
{
    //cData;
};

void *customer(void *arg)
{
    struct custData *argptr;
    char myName[MAXNAME];
    int myVTime, myRTime;
    int hasWaited = 0;
    argptr = (struct cutData *) arg;
    strcpy(myName, argptr->name);
    myVTime = argptr->vTime;
    myRTime = argptr->rTime;

    pthread_mutex_lock(&customer_lock);
    while(nFreeNurses == 0)
    {
        //wait on condition
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

    string name;

    int elapsedtime = 0, waittime = 0, safetyprecaution = 0;

    while(cin >> name >> elapsedtime >> waittime >> safetyprecaution)
    {
        sleep(elapsedtime);
        strcpy(argList->name, name);
        pthread_create(&tid[nThreads], NULL, customer, (void *) &argList);
        nThreads++;
    }
}