/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the module-related class for the simple
 *                      module "ChildPool". This is the header file
 *                      containing declarations for functions and
 *                      attributes. The inclusion of this file in ".cc"
 *                      file for the implementation is needed. This module
 *                      is used to generate children
 */

#ifndef __MERRYGOROUND_CHILDPOOL_H_
#define __MERRYGOROUND_CHILDPOOL_H_

#include <omnetpp.h>
#include "ChildArrivalMsg.h"

using namespace omnetpp;

class ChildPool : public cSimpleModule
{
private:
    ChildArrivalMsg *_newChildren;
    cMessage *_nextArrival;
    double _time;
    // Parameters
    double _Q;
    double _Delta;
    double _Lambda;
    double _P;
    // Signals
    simsignal_t _arrivalSignal;
    simsignal_t _bulkSignal;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

#endif
