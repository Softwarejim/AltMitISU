#include <MessageDistributionSystem.hpp>


void MessageDistributionSystem::subscribe(const std::string& msgId, 
                                          osapi::MsgQueue* mq, 
                                          unsigned long id)
{
  /* Something missing */
  osapi::ScopedLock lock(m_);
  InsertResult ir = sm_.insert(std::make_pair(msgId, SubscriberIdContainer()));

  SubscriberIdContainer& sl = ir.first->second;
    
  details::SubscriberId s(mq, id);
    
  SubscriberIdContainer::iterator iter = find(sl.begin(), sl.end(), s);
  if(iter == sl.end())
    sl.push_back(s);
}


void MessageDistributionSystem::unSubscribe(const std::string& msgId, 
                                            osapi::MsgQueue* mq, 
                                            unsigned long id)
{
  osapi::ScopedLock lock(m_);
  auto subListContainerIter = sm_.find(msgId);

  if(subListContainerIter != sm_.end())
  {
    auto& subListContainer = subListContainerIter->second; 

    details::SubscriberId s(mq, id);

    SubscriberIdContainer::iterator iter = find(subListContainer.begin(), subListContainer.end(), s);
    {
      if(iter != subListContainer.end())
      {
       subListContainer.erase(iter);
      }
    }
  }

  // Find SubscriberIdContainer via via iterator 
  // Where else do I need to find this container?
  // The struct std::pair (the element in std::map<>) contains two vars one
  // named first and one named second. (See funktionen std::make_pair() - JFGI)

  // If found. How do you know that an element in a container was not found?
  
  // Create a details::SubscriberId and use that to find the desired subscriber.
  // When found it must be erased

}




