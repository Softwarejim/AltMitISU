#include "Message.h"
#include <pthread.h>
#include <queue>

struct Item
{
    unsigned long id_;
    Message* msg_;
};

class MsgQueue
{
public:
    MsgQueue(unsigned long maxSize);
    void send(unsigned long id, Message* msg = NULL);
    Message* receive(unsigned long& id);
    bool isFull();
    bool isEmpty();
    ~MsgQueue();

private:
    std::queue<Item> messageQueue_;
    unsigned long maxSize_;
    pthread_mutex_t mtx;
    pthread_cond_t sendSignal;
    pthread_cond_t receiveSignal;
};