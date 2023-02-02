/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the header file containing declarations
 *                      for functions and attributes of the class ChildQueue.
 *                      The inclusion of this file in ".cc" file for the
 *                      implementation is needed
 */

#ifndef __MERRYGOROUND_CHILDQUEUE_H_
#define __MERRYGOROUND_CHILDQUEUE_H_

#include <omnetpp.h>
#include <list>
#include <algorithm>
#include "QueueHowManyMsg_m.h"
#include "QueueQuitMsg_m.h"
#include "RemoveFromQueueMsg_m.h"
#include "ChildArrivalMsg.h"
#include "utility.h"

using namespace omnetpp;
using namespace std;


class ChildQueue : public cSimpleModule
{
  private:
    list<Child> _queue;
    simsignal_t _queueTotal;
    simsignal_t _queueQuit;
    simsignal_t _queueServed;
    simsignal_t _queueLength;
    void insertIntoQueue(ChildArrivalMsg* childArrivalMsg);
    void sendHowManyMessage();
    void removeFromQueue(RemoveFromQueueMsg* removeMsg);
    void quitFromQueue(QueueQuitMsg* quitMsg);
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

#endif
