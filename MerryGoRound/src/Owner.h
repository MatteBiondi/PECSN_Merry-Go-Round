#ifndef __MGR_NETWORK_OWNER_H_
#define __MGR_NETWORK_OWNER_H_

#include <omnetpp.h>
#include <string>
#include "utility.h"

using namespace omnetpp;

class Owner : public cSimpleModule
{
  private:
    int _minChildren;
    int _coinPerRide;
    int _totEarn = 0;
    int _nSeats;
    bool _mgrIsFree = true;
    simsignal_t _coinSignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleMgrIsFreeMsg();
    virtual void handleNumChildrenMsg(cMessage *msg);
    virtual void finish() override;
};

#endif
