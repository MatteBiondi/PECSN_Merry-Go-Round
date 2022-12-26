/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "DummyChildPool". This is the file containing
 *                      implementation for the functions.
 */

#include "DummyChildPool.h"

Define_Module(DummyChildPool);

void DummyChildPool::initialize()
{
    // Initialize private attribute of the class
    _Q = par("Q");
    _interarrivalTime = par("interarrivalTime");
    _bulk = par("bulk");

    // Generate the message for next children creation
    _nextArrival = new cMessage(CREATE_CHILDREN);


    scheduleAt(simTime()+_interarrivalTime, _nextArrival);
}

void DummyChildPool::handleMessage(cMessage *msg)
{
    // Check that the received message is the self message (obvious for the module)
    if(msg->isSelfMessage()){

        // Create message to be sent to ChildQueue
        _newChildren = new ChildArrivalMsg();

        // Generate _bulk children and add them to the message
        for (int i = 0; i < _bulk; ++i){
            double quitTime = simTime().dbl() + _Q;
            _newChildren->addChild(quitTime);
        }

        // Send the message
        send(_newChildren, "toChildQueue");

        // Schedule next arrival
        scheduleAt(simTime()+_interarrivalTime, _nextArrival);
    }
}

void DummyChildPool::finish() {
    if (_nextArrival->isScheduled())
        cancelAndDelete(_nextArrival);
    else
        delete _nextArrival;
}
