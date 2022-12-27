#include "MerryGoRound.h"

Define_Module(MerryGoRound);

void MerryGoRound::initialize()
{
    _T = par("T");
    _rideStart = registerSignal("rideStart");
    _rideStop = registerSignal("rideStop");
    _rideFinishedMsg = new cMessage("rideFinished");
    _rideFinishedMsg->setSchedulingPriority(MEDIUM_PRIORITY); //medium priority
}

void MerryGoRound::handleMessage(cMessage *msg)
{
    if(msg -> isName(START_MGR)){
        emit(_rideStart, simTime().dbl());
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
