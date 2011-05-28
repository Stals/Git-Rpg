#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include <queue>
#include <string>
#include <map>

enum eventType {
    levelUp,
    Achievement,
    Notification
};
struct eventPair {
    eventType eType;
    std::string message;
    eventPair(eventType _eType,std::string _message):eType(_eType),message(_message){}
    eventPair():eType(),message(""){}
};
//typedef  std::pair<eventType,std::string> eventPair;
class eventQueue
{
public:
    eventQueue();
    bool empty();//Возвращает true если queue пустой иначе false
    eventPair pop();
    void push(eventType,std::string);


private:
   std::queue<eventPair> queue;

};
extern eventQueue eQueue;
#endif // EVENTQUEUE_H
