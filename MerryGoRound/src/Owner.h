#ifndef __MGR_NETWORK_OWNER_H_
#define __MGR_NETWORK_OWNER_H_

#include <omnetpp.h>
#include <string>
#include "utility.h"
#include "MerryGoRound.h"
#include "RemoveFromQueueMsg_m.h"
#include "QueueHowManyMsg_m.h"

using namespace omnetpp;
using namespace std;

class Owner : public cSimpleModule
{
  private:
    int _minChildren;
    double _coinPerRide;
    int _totEarn = 0;
    int _nSeats;
    bool _mgrIsFree = true;
    simsignal_t _coinSignal;
    simsignal_t _peopleOnBoardSignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleMgrIsFreeMsg();
    virtual void handleNumChildrenMsg(cMessage *msg);
    virtual void finish() override;
};

#endif
