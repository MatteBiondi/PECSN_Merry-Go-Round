#include "Owner.h"
#include "RemoveFromQueueMsg_m.h"

Define_Module(Owner);

void Owner::initialize()
{
    _minChildren = par("v");
    _coinPerRide = par("c");
    _nSeats = par("N");
    _coinSignal = registerSignal("earnedCoins");
}

void Owner::handleMessage(cMessage *msg)
{
    if(msg -> isName(_MRGISFREEMSG))
        handleMrgIsFreeMsg();
    if(msg -> isName(_NUMCHILDRENMSG))
        handleNumChildrenMsg();
}

void Owner::handleMrgIsFreeMsg(){
    _mgrIsFree = true;
    cMessage *msg = new cMessage(_HOWMANYCHILDRENMSG);
    msg->setSchedulingPriority(2); //highest priority
    send(msg, "outToQueue");
}

void Owner::handleNumChildrenMsg(){
    if(!_mgrIsFree)
        return;
    int num;    //get through the custom message
    if(num >= _minChildren){
        RemoveFromQueueMsg *msg = new RemoveFromQueueMsg(_REMOVEFROMQUEUEMSG);
        if(num >= _nSeats){
            //send msg asking for _N children
            msg -> setHowMany(_nSeats);
            _totEarn += _nSeats*_coinPerRide;
            emit(_coinSignal, _nSeats*_coinPerRide);
        }
        else{
            //send msg asking for num children
            msg -> setHowMany(num);
            _totEarn += num*_coinPerRide;
            emit(_coinSignal, num*_coinPerRide);
        }
        msg->setSchedulingPriority(2); //highest priority
        send(msg, "outToQueue");
        cMessage *startMRG = new cMessage(_STARTMRGMSG);
        startMRG->setSchedulingPriority(2);
        send(startMRG, "outToMRG");
        _mgrIsFree = false;
    }
}
