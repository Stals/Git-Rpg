#include "eventqueue.h"

eventQueue eQueue;
eventQueue::eventQueue(){

}
void eventQueue::push(eventType eType,std::string message){
    eventPair pair(eType,message);

    queue.push(pair);


}
eventPair eventQueue::pop(){
    eventPair pair;
    pair=queue.front();

    queue.pop();
    return pair;
}
bool eventQueue::empty(){

    if(queue.size()==0){
        return true;
    }else{
        return false;
    }
}
