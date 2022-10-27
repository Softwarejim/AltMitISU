#include "MsgQueue.h"
#include <pthread.h>

MsgQueue::MsgQueue(unsigned long maxSize)
{
    pthread_mutex_init(&mtx, NULL);
    pthread_cond_init(&signal_senders, NULL);
    pthread_cond_init(&signal_receivers, NULL);
    maxSize_ = maxSize;
}


bool MsgQueue::isFull()
{
    return messageQueue_.size() >= maxSize_;
}

bool MsgQueue::isEmpty()
{
    return messageQueue_.empty();
}

void MsgQueue::send(unsigned long id, Message* msg)
{
    pthread_mutex_lock(&mtx);
    while(isFull())
    {
        pthread_cond_wait(&signal_senders, &mtx);   //Wait for signal from recievers that element is taken
    }

    messageQueue_.emplace(Item{id, msg});           //Place element in back of queue

    pthread_cond_signal(&signal_receivers);         //Signal to recievers that item is send
    pthread_mutex_unlock(&mtx);
}

Message* MsgQueue::receive(unsigned long & id)
{
    pthread_mutex_lock(&mtx);
    while (isEmpty())
    {
        pthread_cond_wait(&signal_receivers,&mtx);  //Waiting for signal from senders, that element is placed
    }
    
    Item item = messageQueue_.front();              //Look at item
    messageQueue_.pop();                            //Remove item
    
    id = item.id_;                                  //Way to return changed ID
    
    pthread_cond_signal(&signal_senders);           //Signal to sender that item i taken
    pthread_mutex_unlock(&mtx);

    return item.msg_;
}

MsgQueue::~MsgQueue()
{
    pthread_mutex_destroy(&mtx);
    pthread_cond_destroy(&signal_senders);
    pthread_cond_destroy(&signal_receivers);
}