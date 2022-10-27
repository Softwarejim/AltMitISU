#ifndef EXITGUARDTHREAD_HPP
#define EXITGUARDTHREAD_HPP

#include <osapi/ThreadFunctor.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Thread.hpp>
#include <osapi/Conditional.hpp>
#include <messages.hpp>
#include <osapi/Mutex.hpp>
#include <osapi/Utility.hpp>
#include <outputMessages.hpp>
#include <string>
#define QUEUE_SIZE 20

class ExitGuardThread : public osapi::ThreadFunctor
{
public: 
    ExitGuardThread();
    osapi::MsgQueue* getMsgQueue();

protected:
    virtual void run();

private:
    void handleMsg(unsigned long id, osapi::Message* msg);
    void handleReq(exitDoorOpenReq* req);
    void handleInd(carPassedExitDoorInd*(msg));

    osapi::MsgQueue mq_;
    bool running_;
    std::string name_;
    int countCars_ = 0;

};

#endif