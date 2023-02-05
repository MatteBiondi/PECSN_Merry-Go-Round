/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "MerryGoRound". This is the file containing
 *                      implementation for the functions.
 */

#include "MerryGoRound.h"

Define_Module(MerryGoRound);

/**
 * Initialize private attributes of the class and generate the self-message to notify the stop of a MGR ride
 */
void MerryGoRound::initialize()
{
    _T = par("T");
    _rideStop = registerSignal("rideStop");
    _rideFinishedMsg = new cMessage(RIDE_FINISHED);
    _rideFinishedMsg->setSchedulingPriority(MEDIUM_PRIORITY); //medium priority
}

/**
 * If the received message is 'Start_MGR', it schedule the self message in order to simulate a ride
 *
 * If the received message is the self-message, it means that the ride has finished and it has
 * to notify the owner
 *
 * @param msg message received by the current module
 */
void MerryGoRound::handleMessage(cMessage *msg)
{
    if(msg -> isName(START_MGR)){
        scheduleAfter(_T, _rideFinishedMsg);
        delete msg;
    }
    if(msg -> isSelfMessage()){
        //if simTime is smaller than that value it means that the ride started during the warm-up period, so it must not be considered
        if(simTime() - getSimulation()->getWarmupPeriod() >= _T)
            emit(_rideStop, _T);
        cMessage *msg = new cMessage(MGR_IS_FREE);
        msg->setSchedulingPriority(MEDIUM_PRIORITY);  //medium priority
        send(msg, "out");
    }
}

void MerryGoRound::finish(){
    emit(_rideStop, 0); //to compute the final utilization of the MGR
    //check if the message is still in the FES
    if(_rideFinishedMsg -> isScheduled())
        cancelAndDelete(_rideFinishedMsg);
    else
        delete _rideFinishedMsg;
}

int MerryGoRound::getT(){return _T;}
