#ifndef __MGR_NETWORK_MERRYGOROUND_H_
#define __MGR_NETWORK_MERRYGOROUND_H_

#include <omnetpp.h>

using namespace omnetpp;

class MerryGoRound : public cSimpleModule
{
  private:
    simtime_t _T; //how many seconds a ride lasts
    cMessage *_rideFinishedMsg; //loopback message
    const char* _STARTMRGMSG = "startMrg_msg"; //number 7
    const char* _MRGISFREEMSG = "mrgIsFree_msg"; //number 5

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
