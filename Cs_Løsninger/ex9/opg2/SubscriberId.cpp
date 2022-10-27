#include <SubscriberId.hpp>

namespace details 
{

  SubscriberId::SubscriberId(osapi::MsgQueue* mq_, unsigned long id_)
  {
    this->mq_= mq_;
    this->id_ = id_;
  }
  
  
  /** Send the message to the subscriber
   */
  void SubscriberId::send(osapi::Message* m) const
  {
    mq_->send(id_, m);
    
    /* What do you do when you want to send to a reciever?
       What do you need to know? */
  }


}
