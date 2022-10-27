#ifndef CARTHREAD_HPP
#define CARTHREAD_HPP

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Conditional.hpp>
#include <osapi/Mutex.hpp>
#include <osapi/MsgQueue.hpp>
#include <messages.hpp>
#include <osapi/Utility.hpp>
#include <outputMessages.hpp>
#include <string>
#define QUEUE_SIZE 20

class CarThread : public osapi::ThreadFunctor
{
public: 
    CarThread(std::string* name, osapi::MsgQueue* entryGuardQueue, osapi::MsgQueue* exitGuardQueue);
    osapi::MsgQueue* getMsgQueue();

protected:
    virtual void run();

private:
    void handleMsg(unsigned long id, osapi::Message* msg);
    void carHandleStartInd(startInd* ind);
    void carHandleEntryDoorOpenCfm(entryDoorOpenCfm* cfm);
    void carDriveOutInd(exitInd* ind);
    void carHandleExitDoorOpenCfm(exitDoorOpenCfm* cfm);

    osapi::MsgQueue* exitGuardMq_;
    osapi::MsgQueue* entryGuardMq_;
    osapi::MsgQueue mq_;
    bool running_;
    std::string name_;
};

#endif