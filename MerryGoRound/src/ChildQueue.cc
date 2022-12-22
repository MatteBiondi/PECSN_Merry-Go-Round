//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "ChildQueue.h"

using namespace omnetpp;
using namespace std;

Define_Module(ChildQueue);

void ChildQueue::initialize(){
    this->_queue = list<Child>();
    this->queueTotalCount = registerSignal("queueTotalCount");
    this->queueQuitCount = registerSignal("queueQuitCount");
}

void ChildQueue::handleMessage(cMessage *msg){
    string msgSender = msg->getSenderModule()->getName();

    if(msgSender.compare("ChildPool") == 0 && msg->isName(CHILD_ARRIVAL)){
        ChildArrivalMsg* childArrivalMsg = check_and_cast<ChildArrivalMsg*>(msg);
        // Queue up the new children and schedule drop events
        insertIntoQueue(childArrivalMsg);
        // Send how many children are queued to owner
        sendHowManyMessage();
        delete childArrivalMsg;
    }
    else if(msgSender.compare("Owner") == 0 && msg->isName(HOWMANY_REQUEST)){
        // Send how many children are queued to owner
        sendHowManyMessage();
        delete msg;
    }
    else if(msgSender.compare("Owner") == 0 && msg->isName(REMOVE_FROM_QUEUE)){
        // Delete served children from queue
        RemoveFromQueueMsg* removeMsg = check_and_cast<RemoveFromQueueMsg*>(msg);
        removeFromQueue(removeMsg);
        delete removeMsg;
    }
    else if(msg->isSelfMessage() && msg->isName(QUIT_CHILD)){
        // Delete quitting child from queue
        QueueQuitMsg* quitMsg = check_and_cast<QueueQuitMsg*>(msg);
        quitFromQueue(quitMsg);
        delete quitMsg;
    }
    else{
        EV_WARN << "Unexpected message {"<< msg->getName() << ", " << msgSender << "}" << endl;
        delete msg;
    }
}

/*
 * Message handler functions
 */

void ChildQueue::insertIntoQueue(ChildArrivalMsg* childArrivalMsg){
    for(int i = 0; i < childArrivalMsg->getNumChildren(); ++i){
        Child child(childArrivalMsg->getChild(i));
        QueueQuitMsg* quitMessage = new QueueQuitMsg(QUIT_CHILD);
        this->_queue.push_back(child);

        // Schedule possible quit event
        quitMessage->setChild(childArrivalMsg->getChild(i));
        quitMessage->setSchedulingPriority(3);
        scheduleAt(child.getQuitTime(), quitMessage);
    }
    emit(this->queueTotalCount, childArrivalMsg->getNumChildren());
}

void ChildQueue::sendHowManyMessage(){
    QueueHowManyMessage* queueMsg = new QueueHowManyMessage(HOWMANY_CHILDREN);
    queueMsg->setHowMany(this->_queue.size());
    queueMsg->setSchedulingPriority(1);
    send(queueMsg, "ownerOut");
    EV_INFO << "There are " << this->_queue.size() << " children waiting in queue" << endl;
}

void ChildQueue::removeFromQueue(RemoveFromQueueMsg* removeMsg){
    if(removeMsg->getHowMany() > 0 && this->_queue.size() <= (size_t)removeMsg->getHowMany()){
        throw cRuntimeError("Owner requested more children than available in queue (%d, %lu)",removeMsg->getHowMany(), this->_queue.size());
    }
    for(int i = 0; i < removeMsg->getHowMany(); ++i){
        this->_queue.pop_front();
    }
    EV_INFO << "Remove "<< removeMsg->getHowMany() << " children from queue" << endl;
}

void ChildQueue::quitFromQueue(QueueQuitMsg* quitMsg){
    list<Child>::iterator queueQuitChild = find(this->_queue.begin(), this->_queue.end(), quitMsg->getChild());
    if(queueQuitChild != this->_queue.end()){
        this->_queue.erase(queueQuitChild);
        emit(this->queueQuitCount, 1);
        EV_INFO << "Child quits from queue" << endl;
    }
}
