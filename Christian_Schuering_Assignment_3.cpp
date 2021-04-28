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
    string name = NULL;
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
        strcpy(argList.name, name);
        pthread_create(&tid[nThreads], NULL, customer, (void *) &argList);
        nThreads++;
    }
}