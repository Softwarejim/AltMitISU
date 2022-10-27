#include "MsgQueue.h"


MsgQueue::MsgQueue(unsigned long maxSize)
{
    pthread_mutex_init(&mtx, NULL);                 //initier mutex            
    pthread_cond_init(&sendSignal, NULL);           //initier conditional variabel
    pthread_cond_init(&receiveSignal, NULL);        //initier conditional variabel

    maxSize_ = maxSize;
}
    
void MsgQueue::send(unsigned long id, Message* msg)
{
    pthread_mutex_lock(&mtx);                       //Lock mutex                                                           

    while(isFull())                                 //Hvis quen er fuld, bloker tråd, frigiv mutex, afvent receiveSignal. 
        pthread_cond_wait(&receiveSignal, 
                              &mtx); 

    messageQueue_.emplace(Item{id, msg});           //Kø ikke fuld, tilføj item. 

    pthread_cond_signal(&sendSignal);               // Signaler til receiver at queue ikke længere er tom. 
    pthread_mutex_unlock(&mtx);
}

Message* MsgQueue::receive(unsigned long& id)
{
    pthread_mutex_lock(&mtx);                       //Lock mutex

    while(isEmpty())                                //Hvis queuen er tom, bloker tråd, frigiv mutex, afvent sendSignal
        pthread_cond_wait(&sendSignal, 
                              &mtx); 
    
    Item item = messageQueue_.front();              //Hvis køen ikke er tom, kopier item fra queuen til nyt item objekt. 
    messageQueue_.pop();                            //Fjern den kopierede item objekt. 
    id = item.id_;                                  //Sætter id.

    pthread_cond_signal(&receiveSignal);            //Signaler til sender at queue ikke længere er fuld
    pthread_mutex_unlock(&mtx);                     //Unlock mutex

    return item.msg_;
}

bool MsgQueue::isFull()
{
    return (messageQueue_.size() == maxSize_ ? true : false); //returner om queuen er fuld
}

bool MsgQueue::isEmpty()
{
    return (messageQueue_.size() == 0 ? true : false);  // returner om queuen er tom
}

MsgQueue::~MsgQueue()                               
{
    pthread_mutex_destroy(&mtx);                        //nedlæg mutex         
    pthread_cond_destroy(&sendSignal);                  //nedlæg conditional variabel
    pthread_cond_destroy(&receiveSignal);               //nedlæg conditional variabel
}

    