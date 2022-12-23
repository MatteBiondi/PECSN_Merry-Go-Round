#include "Owner.h"
#include "RemoveFromQueueMsg_m.h"
#include "QueueHowManyMsg_m.h"

Define_Module(Owner);

void Owner::initialize()
{
    _nSeats = par("N");
    _minChildren = _nSeats * (double)par("v_fraction");
    _coinPerRide = par("c");
    _coinSignal = registerSignal("earnedCoins");
}

void Owner::handleMessage(cMessage *msg)
{
    if(msg -> isName(MRG_IS_FREE)){
        handleMrgIsFreeMsg();
        delete msg;
    }
    else if(msg -> isName(HOWMANY_CHILDREN))
        handleNumChildrenMsg(msg);
}

//handler of the message sent by the MGR, signaling that it has finished the ride
void Owner::handleMrgIsFreeMsg(){
    _mgrIsFree = true;
    cMessage *msg = new cMessage(HOWMANY_REQUEST);
    msg->setSchedulingPriority(HIGH_PRIORITY); //highest priority
    send(msg, "outToQueue");
}

//handler of the message sent by the queue, signaling the actual number of children in it
void Owner::handleNumChildrenMsg(cMessage *receivedMsg){
    QueueHowManyMessage *queueHowManyMessage = check_and_cast<QueueHowManyMessage*>(receivedMsg);
    //if the MGR is busy, I can not accept new children to ride
    if(!_mgrIsFree){
        delete queueHowManyMessage;
        return;
    }


    int num = queueHowManyMessage -> getHowMany();

    if(num >= _minChildren){
        //if the number of children is above the threshold I can ask for removing some of them to enjoy a ride
        RemoveFromQueueMsg *msg = new RemoveFromQueueMsg(REMOVE_FROM_QUEUE);
        if(num >= _nSeats){
            //if there are more children than the MGR capacity, I have to ask for the maximum number, the capacity itself
            msg -> setHowMany(_nSeats);
            _totEarn += _nSeats*_coinPerRide;
            emit(_coinSignal, _nSeats*_coinPerRide);
        }
        else{
            //otherwise I ask for all the children in the queue
            msg -> setHowMany(num);
            _totEarn += num*_coinPerRide;
            emit(_coinSignal, num*_coinPerRide);
        }
        msg->setSchedulingPriority(HIGH_PRIORITY); //highest priority
        send(msg, "outToQueue");
        cMessage *startMRG = new cMessage(START_MRG);
        startMRG->setSchedulingPriority(HIGH_PRIORITY);
        send(startMRG, "outToMGR");
        _mgrIsFree = false;
    }

    delete queueHowManyMessage;
}
