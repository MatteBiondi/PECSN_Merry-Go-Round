/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "Owner". This is the header file
 *                      containing declarations for functions and
 *                      attributes. The inclusion of this file in ".cc"
 *                      file for the implementation is needed. This module
 *                      is used to handle the MGR activation and decide
 *                      with how many people
 */

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
    //Parameters
    int _minChildren;
    double _coinPerRide;
    int _totEarn = 0;
    int _nSeats;
    bool _mgrIsFree = true;
    //Signals
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
