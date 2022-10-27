#ifndef ENTRYGUARDTHREAD_HPP
#define ENTRYGUARDTHREAD_HPP

#include <boost/shared_ptr.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Conditional.hpp>
#include <osapi/Mutex.hpp>
#include <messages.hpp>
#include <osapi/Utility.hpp>
#include <outputMessages.hpp>
#include <string>
#define QUEUE_SIZE 20

class EntryGuardThread : public osapi::ThreadFunctor
{
public: 
    EntryGuardThread();
    osapi::MsgQueue* getMsgQueue();

protected:
    virtual void run();

private:
    void handleMsg(unsigned long id, osapi::Message* msg);
    void handleReq(entryDoorOpenReq* req);
    void handleInd(carPassedEntryDoorInd* msg);

    osapi::MsgQueue mq_;
    bool running_;
    std::string name_;
    int countCars_ = 0;

};
#endif