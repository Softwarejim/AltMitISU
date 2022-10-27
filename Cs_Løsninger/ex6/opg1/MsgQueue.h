#include "Message.h"
#include <queue>
#include <pthread.h>



class MsgQueue : public Message
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message* receive(unsigned long & id);
    ~MsgQueue();
    bool isFull();
    bool isEmpty();
private:

    unsigned long maxSize_;
    struct Item
    {
        unsigned long id_;
        Message* msg_;
    };
    std::queue<Item> messageQueue_;
    pthread_mutex_t mtx;
    pthread_cond_t signal_senders;      // Signal to sender that element taken
    pthread_cond_t signal_receivers;    // Signal to reciever that element is send
};