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

    //pthread_mutex_lock(&customer_lock);
    if(nFreeNurses == 0)
    {
        //wait on condition
        pthread_mutex_unlock(&customer_lock);
        nFreeNurses++; //need free nurses
    }
    
    //update counters and print customer is getting jab
    //pthread_mutex_unlock(&customer_lock);
    sleep(myRTime); //allergic reaction trial time
    //pthread_mutex_lock(&customer_lock);
        //update counters and print customer got vaccinated
        //signal condition
    //pthread_mutex_unlock(&customer_lock);
    cout << argptr->cname << " leaves the center." << endl;
}

int main(int argc, char* argv[])
{
    //ifstream input;
    Arguments * head = nullptr;
    Arguments argList;
    pthread_t tid[NMAX];

    pthread_mutex_init(&customer_lock, nullptr);
    //pthread_join(tid[NMAX], NULL);

    int nThreads = 0;

    if(argc > 2) //parsing in
    {
        cout << "Wrong number of arguments" << endl;
        return 0;
    }
    else
    {
        int temp = stoi(argv[1]);
        nThreads = temp;
        nFreeNurses = temp;
    }

    ofstream fout("output.txt");
    ifstream fin("input30.txt");
    fin.open("input30.txt");

    while(cin >> argList.cname >> argList.elapsedtime >> argList.waittime >> argList.safetyprecaution)
    {
        head = argList.next;
    } //parsing in as a linked list

    for(int i = 0; i < nThreads; i++)
    {
        sleep(argList.waittime);
        pthread_create(&tid[i], nullptr, customer, (void*) &argList); //creates list
    }

    for(int i = 0; i < nCustomers; i++) pthread_join(tid[i], nullptr); //joins together

    //minutia
    cout << nVacced << " customer(s) were vaccinated." << endl;
    fout << nVacced << " customer(s) were vaccinated." << endl;

    cout << nHadToWait << " people had to wait." << endl;
    fout << nHadToWait << " people had to wait." << endl;

    return 0;
}