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
    if(msg -> isName(START_MRG)){
        emit(_rideStart, simTime().dbl());
        scheduleAfter(_T, _rideFinishedMsg);
        delete msg;
    }
    if(msg -> isSelfMessage()){
        emit(_rideStop, _T);
        cMessage *msg = new cMessage(MRG_IS_FREE);
        msg->setSchedulingPriority(MEDIUM_PRIORITY);  //medium priority
        send(msg, "out");
    }
}

void MerryGoRound::finish(){
    //check if the message is still in the FES
    if(_rideFinishedMsg -> isScheduled())
        cancelAndDelete(_rideFinishedMsg);
    else
        delete _rideFinishedMsg;
}
