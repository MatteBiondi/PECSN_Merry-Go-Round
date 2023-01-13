/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "MerryGoRound". This is the header file
 *                      containing declarations for functions and
 *                      attributes. The inclusion of this file in ".cc"
 *                      file for the implementation is needed. This module
 *                      is used to represents MGR rides
 */

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
    simsignal_t _rideStop;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

  public:
    virtual int getT();
};

#endif
