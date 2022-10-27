#include "MsgQueue.h"

MsgQueue::MsgQueue(unsigned long maxSize)
{
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&sendSignal, NULL);
    pthread_cond_init(&receiveSignal, NULL);

    maxSize_ = maxSize;
}
    
void MsgQueue::send(unsigned long id, Message* msg)
{
    pthread_mutex_lock(&mtx);

    while(isFull())                           
        pthread_cond_wait(&receiveSignal, 
                              &mtx); 
    messageQueue_.emplace(Item{id, msg});

    pthread_cond_signal(&sendSignal);
    pthread_mutex_unlock(&mtx);
}

Message* MsgQueue::receive(unsigned long& id)
{
    pthread_mutex_lock(&mtx);

    while(isEmpty())                           
        pthread_cond_wait(&sendSignal, 
                              &mtx); 
    
    Item item = messageQueue_.front();
    messageQueue_.pop();
    id = item.id_;

    pthread_cond_signal(&receiveSignal);
    pthread_mutex_unlock(&mtx);

    return item.msg_;
}

bool MsgQueue::isFull()
{
    return (messageQueue_.size() == maxSize_ ? true : false);
}

bool MsgQueue::isEmpty()
{
    return (messageQueue_.size() == 0 ? true : false);
}

MsgQueue::~MsgQueue()
{
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&sendSignal);
    pthread_cond_destroy(&receiveSignal);
}

    