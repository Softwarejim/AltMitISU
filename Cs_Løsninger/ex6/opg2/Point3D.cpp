#include "MsgQueue.h"
#include <unistd.h>
#include <iostream>
using namespace std;
#define MESSAGE_ID 584
#define MAX_SIZE 10

Message msg_;

struct Point3D : public Message
{
    int x;
    int y;
    int z;
};

void handleMessages(unsigned long id, Message* msg);
void handlePoint3DMessage(Point3D* point);
int numberGenerator();

void* Sender(void *d)
{
    MsgQueue* message = (MsgQueue*) d;

    for(;;)
    {
        Point3D* point = new Point3D;
        point->x = numberGenerator();
        point->y = numberGenerator();
        point->z = numberGenerator();

        message->send(MESSAGE_ID, static_cast<Message*>(point));

        sleep(1);
    }

    pthread_exit(NULL);
}

void* Receiver(void *d)
{
    MsgQueue* message = (MsgQueue*) d;

    for(;;)
    {
        unsigned long id;
        Message* msg = message->receive(id);
        handleMessages(id, msg);
        delete(msg);
    }

    pthread_exit(NULL);
}

void handleMessages(unsigned long id, Message* msg)
{
    switch(id)
    {
    case MESSAGE_ID:
    handlePoint3DMessage(static_cast<Point3D*>(msg));
    break;
    }
}

void handlePoint3DMessage(Point3D* point)
{
    cout << point->x << ", " << point->y << ", " << point->z << endl;
}

int numberGenerator()
{
    return rand() % 10 + 1;
}

int main()
{
    srand (time(NULL));

    MsgQueue msgQueue_(MAX_SIZE);
    pthread_t sender;
    pthread_t receiver;

    pthread_create(&sender, nullptr, Sender, static_cast <void*> (&msgQueue_));
    pthread_create(&receiver, nullptr, Receiver, static_cast <void*> (&msgQueue_));

    pthread_join(sender, NULL);
    pthread_join(receiver, NULL);

    return 0;
}