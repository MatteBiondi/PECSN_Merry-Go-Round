#include "Owner.h"

Define_Module(Owner);

void Owner::initialize()
{
    _nSeats = par("N");
    _minChildren = _nSeats * (double)par("v_fraction");
    _coinPerRide = par("c");
    _coinSignal = registerSignal("earnedCoins");
    _peopleOnBoardSignal = registerSignal("peopleOnBoard");
}

void Owner::handleMessage(cMessage *msg)
{
    if(msg -> isName(MGR_IS_FREE)){
        handleMgrIsFreeMsg();
        delete msg;
    }
    else if(msg -> isName(HOWMANY_CHILDREN))
        handleNumChildrenMsg(msg);
}

//handler of the message sent by the MGR, signaling that it has finished the ride
void Owner::handleMgrIsFreeMsg(){
    _mgrIsFree = true;
    cMessage *msg = new cMessage(HOWMANY_REQUEST);
    msg->setSchedulingPriority(MEDIUM_PRIORITY); //medium priority
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

    //get the T parameter from the mgr in order to check if we can start a ride
    MerryGoRound  *mgr_module = check_and_cast<MerryGoRound*>(findModuleByPath("merryGoRound"));
    int T = mgr_module->getT();

    //if there is no enough time to complete a ride, it will not start
    SimTime limit = SimTime::parse(getEnvir() -> getConfig() -> getConfigValue("sim-time-limit"));
    if(simTime().dbl() + T > limit.dbl()){
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
            emit(_coinSignal, (double)_nSeats*_coinPerRide);
            emit(_peopleOnBoardSignal, _nSeats);
        }
        else{
            //otherwise I ask for all the children in the queue
            msg -> setHowMany(num);
            _totEarn += num*_coinPerRide;
            emit(_coinSignal, (double)num*_coinPerRide);
            emit(_peopleOnBoardSignal, num);
        }
        msg->setSchedulingPriority(HIGH_PRIORITY); //highest priority
        send(msg, "outToQueue");
        cMessage *startMGR = new cMessage(START_MGR);
        startMGR->setSchedulingPriority(HIGH_PRIORITY);
        send(startMGR, "outToMGR");
        _mgrIsFree = false;
    }

    delete queueHowManyMessage;
}

void Owner::finish(){
    emit(_coinSignal, 0.0);
}
