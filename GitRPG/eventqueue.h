#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include <queue>
#include <string>
#include <map>

enum eventType {
    levelUp,
    achievement,
    notification,
    progress
};
struct eventPair {
    eventType eType;
    std::string message;
    eventPair(eventType _eType,std::string _message):eType(_eType),message(_message){}
    eventPair():eType(),message(""){}
};

class eventQueue
{
public:
    eventQueue();
    bool empty();//���������� true ���� queue ������ ����� false
    eventPair pop();//���������� ������� �� ������ ������� , � ������� ��� �� queue
    void push(eventType,std::string);//��������� ������� � ����� �������


private:
    std::queue<eventPair> queue;

};
extern eventQueue eQueue;




#endif // EVENTQUEUE_H
