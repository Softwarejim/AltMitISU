#include <SubscriberId.hpp>

namespace details 
{

  SubscriberId::SubscriberId(osapi::MsgQueue* mq, unsigned long id) : mq_(mq), id_(id)
  {
    /* Make your own implementation here... */

  }
  
  
  /** Send the message to the subscriber
   */
  void SubscriberId::send(osapi::Message* m) const
  {
    /* What do you do when you want to send to a reciever?
       What do you need to know? */
      mq_->send(id_, m);
  }


}
