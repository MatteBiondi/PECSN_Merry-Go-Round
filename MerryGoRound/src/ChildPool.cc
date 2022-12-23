/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "ChildPool". This is the file containing
 *                      implementation for the functions.
 */

#include "ChildPool.h"

Define_Module(ChildPool);

void ChildPool::initialize()
{
    // Initialize private attribute of the class
    _Q = par("Q");
    _Delta = par("Delta");
    _Lambda = par("Lambda");
    _P = par("P");

    // Generate the message for next children creation
    _nextArrival = new cMessage(CREATE_CHILDREN);
    _time = exponential(_Lambda);
    scheduleAt(simTime()+_time, _nextArrival);
}

void ChildPool::handleMessage(cMessage *msg)
{
    // Check that the received message is the self message (obvious for the module)
    if(msg->isSelfMessage()){
        // Extract a random number of children to be generated
        int n = geometric(_P) + 1;

        // Create message to be sent to ChildQueue
        _newChildren = new ChildArrivalMsg();

        // Generate n children and add them to the message
        for (unsigned int i = 0; i < n; ++i){
            double quitTime = simTime().dbl() + _Q + exponential(_Delta);
            _newChildren->addChild(quitTime);
        }

        // Send the message
        send(_newChildren, "toChildQueue");

        // Generate the message for next children creation
        _time = exponential(_Lambda);
        scheduleAt(simTime()+_time, _nextArrival);
    }
}
