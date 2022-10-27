#include <osapi/Log.hpp>
#include <Subscriber.hpp>

static const int MAX_QUEUE_SIZE=10;


Subscriber::Subscriber(unsigned int subId)
  :  mq_(MAX_QUEUE_SIZE), subId_(subId)
{
  /*****************************************************/
  /*****************************************************/
  /* Write the necessary code to subscribe to an event */
  /*****************************************************/
  /*****************************************************/  
  MessageDistributionSystem::getInstance().subscribe(HELLO_MSG, &mq_, ID_HELLO); // subscribe til hello_mesg og kald hanlder udfra ID
}


Subscriber::~Subscriber()
{
  mq_.send(ID_TERMINATE);
}

void Subscriber::handleMsgIdHello(HelloMsg* hm)
{
  OSAPI_LOG_DBG("S(" << subId_ << ") The hello message contained: '" << hm->data_ << "'");

  /*******************************************************/
  /*******************************************************/
  /* Write the necessary code to unsubscribe to an event */
  /*******************************************************/
  /*******************************************************/    
  MessageDistributionSystem::getInstance().unSubscribe(HELLO_MSG, &mq_, ID_HELLO); //Handler er kaldt og der unsubscribes, derfor kommer
  //der kun ét output af beskeden, havde denne været udkommenteret, var der kommet flere. Teknisk set kan der godt komme flere
  //trod vi udkommenterer, det er et spørgsmål om timing, så hvis publisher sender to msg lige efter hinanden, foer unsubscribe
  //kaldes, så kommer 2 beskeder.
}




void Subscriber::handleMsg(unsigned long id, osapi::Message* msg)
{
  switch(id)
  {
    case ID_HELLO:
      handleMsgIdHello(static_cast<HelloMsg*>(msg));
      break;
        
    case ID_TERMINATE:
      OSAPI_LOG_DBG("S(" << subId_ << ") Got terminate signal");
      break;
  }
    
}


void Subscriber::run()
{
  OSAPI_LOG_DBG("Preparing for loop...");

  while(running_)
  {
    unsigned long id;
    osapi::Message* m = mq_.receive(id);
    handleMsg(id, m);
    delete m;
  }

  OSAPI_LOG_DBG("Thread terminating...");
}
