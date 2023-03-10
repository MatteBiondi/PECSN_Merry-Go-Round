/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "ChildPool". This is the file containing
 *                      implementation for the functions.
 */

#include "ChildPool.h"

Define_Module(ChildPool);

/**
 * Initialize private attributes of the class and generate the message for next children creation
 */
void ChildPool::initialize()
{
    // Initialize private attribute of the class
    _Q = par("Q");
    _Delta = par("Delta");
    _Lambda = par("Lambda");
    _P = par("P");
    _arrivalSignal = registerSignal("arrivals");
    _bulkSignal = registerSignal("bulk");

    // Generate the message for next children creation
    _nextArrival = new cMessage(CREATE_CHILDREN);
    _nextArrival->setSchedulingPriority(HIGH_PRIORITY);
    _time = exponential(_Lambda);
    emit(_arrivalSignal, _time);
    scheduleAt(simTime()+_time, _nextArrival);
}


/**
 * If the received message is 'CreateChildren', it randomly draws the number of children to be created,
 * creates them and sends them to the ChildQueue module.
 * Then, it generates the message for next children creation
 *
 * @param msg message received by the current module
 */
void ChildPool::handleMessage(cMessage *msg)
{
    // Check that the received message is the self message
    if(msg->isSelfMessage() && msg->isName(CREATE_CHILDREN)){
        // Extract a random number of children to be generated
        int n = (_P == 1)? 1 : (geometric(_P) + 1);
        emit(_bulkSignal, n);
        // Create message to be sent to ChildQueue
        _newChildren = new ChildArrivalMsg();

        // Generate n children and add them to the message
        for (int i = 0; i < n; ++i){
            //The transformation of the parameters to SimTime is to avoid loss of accuracy
            SimTime quitTime = simTime() + SimTime(_Q) + exponential(SimTime(_Delta));
            _newChildren->addChild(quitTime);
        }

        // Send the message
        send(_newChildren, "toChildQueue");

        // Generate the message for next children creation
        _time = exponential(_Lambda);
        emit(_arrivalSignal, _time);
        scheduleAt(simTime()+_time, _nextArrival);
    }
    else{
        EV_WARN << "Unexpected message {"<< msg->getName() << "}" << endl;
    }
}


/**
 * If the 'CreateChildren' message is scheduled, it will be cancelled. Then it will be deleted.
 */
void ChildPool::finish() {
    if (_nextArrival->isScheduled())
        cancelAndDelete(_nextArrival);
    else
        delete _nextArrival;
}
