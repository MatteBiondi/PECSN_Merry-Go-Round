#include "MerryGoRound.h"

Define_Module(MerryGoRound);

void MerryGoRound::initialize()
{
    _T = par("T");
    _rideFinishedMsg = new cMessage("rideFinished");
    _rideFinishedMsg->setSchedulingPriority(1); //medium priority
}

void MerryGoRound::handleMessage(cMessage *msg)
{
    if(msg -> isName(_STARTMRGMSG)){
        scheduleAfter(_T, _rideFinishedMsg);
    }
    if(msg -> isSelfMessage()){
        cMessage *msg = new cMessage(_MRGISFREEMSG);
        msg->setSchedulingPriority(1);  //medium priority
        send(msg, "out");
    }
}
