/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "ChildQueue". This is the file containing
 *                      implementation for the functions.
 */

#include "ChildQueue.h"

using namespace omnetpp;
using namespace std;

Define_Module(ChildQueue);

void ChildQueue::initialize(){
    this->_queue = list<Child>();
    this->_queueTotal = registerSignal("queueTotal");
    this->_queueQuit = registerSignal("queueQuit");
    this->_queueServed = registerSignal("queueServed");
    this->_queueLength= registerSignal("queueLength");
}

/**
 * Based on message name the message is casted to the appropriate supertype, handled and then deleted in order to avoid
 * memory leaks
 *
 * @param msg message received by the current module
 */
void ChildQueue::handleMessage(cMessage *msg){
    if(msg->isName(CHILD_ARRIVAL)){
        ChildArrivalMsg* childArrivalMsg = check_and_cast<ChildArrivalMsg*>(msg);
        // Queue up the new children and schedule drop events
        insertIntoQueue(childArrivalMsg);
        // Send how many children are queued to owner
        sendHowManyMessage();
        delete childArrivalMsg;
    }
    else if(msg->isName(HOWMANY_REQUEST)){
        // Send how many children are queued to owner
        sendHowManyMessage();
        delete msg;
    }
    else if(msg->isName(REMOVE_FROM_QUEUE)){
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
        EV_WARN << "Unexpected message {"<< msg->getName() << "}" << endl;
        delete msg;
    }
}


/*******************************/
/*  Message handler functions  */
/*******************************/

/**
 * Insert new children into queue, taking the information needed from the message passed as argument. For each child the
 * possible quit event in the future is scheduled
 *
 * @param childArrivalMsg message received from ChildPool module, containing number of children to add to the queue
 */
void ChildQueue::insertIntoQueue(ChildArrivalMsg* childArrivalMsg){
    for(int i = 0; i < childArrivalMsg->getNumChildren(); ++i){
        Child child(childArrivalMsg->getChild(i));
        QueueQuitMsg* quitMessage = new QueueQuitMsg(QUIT_CHILD);
        this->_queue.push_back(child); // Add child to the back of the queue

        // Schedule possible quit event, if the child is served before the quit message,
        // the event will not produce any effect
        quitMessage->setChild(childArrivalMsg->getChild(i));
        quitMessage->setSchedulingPriority(LOW_PRIORITY);
        scheduleAt(child.getQuitTime(), quitMessage);
        emit(this->_queueTotal, child.getId()); // Increase the total number of children arrived in the system
    }

    emit(this->_queueLength, this->_queue.size()); // Update queue size statistic
}

/**
 * Send the QueueHowManyMessage message to the Owner module. The message contains the number of children currently
 * waiting in the queue
 */
void ChildQueue::sendHowManyMessage(){
    //Build message
    QueueHowManyMessage* queueMsg = new QueueHowManyMessage(HOWMANY_CHILDREN);
    queueMsg->setHowMany(this->_queue.size());
    queueMsg->setSchedulingPriority(HIGH_PRIORITY);

    // Send message to the Owner module
    send(queueMsg, "ownerOut");
    EV_INFO << "There are " << this->_queue.size() << " children waiting in queue" << endl;
}

/**
 * Remove the number of children specified in the message passed as argument
 *
 * @param removeMsg message received from Owner module, containing the number of children that are going to be served,
 * so that must be removed from queue
 * @throws cRuntimeError in case the number of children to remove from queue is higher than the ones currently queued
 */
void ChildQueue::removeFromQueue(RemoveFromQueueMsg* removeMsg){
    if(removeMsg->getHowMany() > 0 && this->_queue.size() < (size_t)removeMsg->getHowMany()){
        throw cRuntimeError("Owner requested more children than available in queue (%d, %lu)",
                            removeMsg->getHowMany(), this->_queue.size());
    }
    for(int i = 0; i < removeMsg->getHowMany(); ++i){
        Child removedChild = this->_queue.front(); //Take the first child in queue, but doesn't remove it from the queue
        emit(this->_queueServed, removedChild.getId()); // Increase the number of children served
        this->_queue.pop_front(); //Remove child from the front of the queue
    }
    emit(this->_queueLength, this->_queue.size());// Update queue size statistic
    EV_INFO << "Remove "<< removeMsg->getHowMany() << " children from queue" << endl;
}

/**
 * Remove from the queue the child identified by the ID contained in the message passed as argument because he has
 * decided to leave the queue before being served
 *
 * @param quitMsg self message containing the ID of the child that wants to leave the queue because he has waited up to
 * his patience limit
 */
void ChildQueue::quitFromQueue(QueueQuitMsg* quitMsg){
    // Find the child having the ID contained in the message, note that the IDs are unique by construction !
    list<Child>::iterator queueQuitChild = find(this->_queue.begin(), this->_queue.end(), quitMsg->getChild());
    if(queueQuitChild != this->_queue.end()){
        this->_queue.erase(queueQuitChild); // Remove the child pointed by iterator
        emit(this->_queueQuit, queueQuitChild->getId()); //Increase the number of children quit from queue
        emit(this->_queueLength, this->_queue.size()); //Update queue size statistic
        EV_INFO << "Child quits from queue" << endl;
    }
}
