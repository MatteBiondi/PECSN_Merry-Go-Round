#ifndef __MGR_NETWORK_MERRYGOROUND_H_
#define __MGR_NETWORK_MERRYGOROUND_H_

#include <omnetpp.h>
#include "utility.h"

using namespace omnetpp;

class MerryGoRound : public cSimpleModule
{
  private:
    int _T; //how many seconds a ride lasts
    cMessage *_rideFinishedMsg; //loopback message
    simsignal_t _rideStart;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif
