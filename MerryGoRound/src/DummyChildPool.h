/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "DummyChildPool". This is the header file
 *                      containing declarations for functions and
 *                      attributes. The inclusion of this file in ".cc"
 *                      file for the implementation is needed. This module
 *                      is used to validate the other modules in the chain,
 *                      generating children deterministically
 */

#ifndef __MERRYGOROUND_DUMMYCHILDPOOL_H_
#define __MERRYGOROUND_DUMMYCHILDPOOL_H_

#include <omnetpp.h>
#include "ChildArrivalMsg.h"

using namespace omnetpp;

class DummyChildPool : public cSimpleModule
{
private:
    ChildArrivalMsg *_newChildren;
    cMessage *_nextArrival;
    int _Q;
    double _interarrivalTime;
    int _bulk;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif
