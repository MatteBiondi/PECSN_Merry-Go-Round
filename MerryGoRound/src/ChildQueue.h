//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

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
    simsignal_t _queueTotalCount;
    simsignal_t _queueQuitCount;
    simsignal_t _queueServedCount;
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
