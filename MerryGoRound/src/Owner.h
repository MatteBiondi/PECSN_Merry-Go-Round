#ifndef __MGR_NETWORK_OWNER_H_
#define __MGR_NETWORK_OWNER_H_

#include <omnetpp.h>
#include <string>

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
    const char* _MRGISFREEMSG = "mrgIsFree_msg"; //number 5
    const char* _NUMCHILDRENMSG = ""; //number 6
    const char* _REMOVEFROMQUEUEMSG = ""; //number 4
    const char* _STARTMRGMSG = "startMrg_msg"; //number 7
    const char* _HOWMANYCHILDRENMSG = ""; //number 9

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleMrgIsFreeMsg();
    virtual void handleNumChildrenMsg();
};

#endif
