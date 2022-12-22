#include "MerryGoRound.h"

Define_Module(MerryGoRound);

void MerryGoRound::initialize()
{
    _T = par("T");
    _rideFinishedMsg = new cMessage("rideFinished");
    _rideFinishedMsg->setSchedulingPriority(MEDIUM_PRIORITY); //medium priority
}

void MerryGoRound::handleMessage(cMessage *msg)
{
    if(msg -> isName(START_MRG)){
        scheduleAfter(_T, _rideFinishedMsg);
    }
    if(msg -> isSelfMessage()){
        cMessage *msg = new cMessage(MRG_IS_FREE);
        msg->setSchedulingPriority(MEDIUM_PRIORITY);  //medium priority
        send(msg, "out");
    }
}
