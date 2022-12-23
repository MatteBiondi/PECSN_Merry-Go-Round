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

#include "DummyChildPool.h"

Define_Module(DummyChildPool);

void DummyChildPool::initialize()
{
    // Initialize private attribute of the class
    _Q = par("Q");
    _interarrivalTime = par("interarrivalTime");
    _bulk = par("bulk");

    // Generate the message for next children creation
    _nextArrival = new cMessage(CREATE_CHILDREN);


    scheduleAt(simTime()+_interarrivalTime, _nextArrival);
}

void DummyChildPool::handleMessage(cMessage *msg)
{
    // Check that the received message is the self message (obvious for the module)
    if(msg->isSelfMessage()){

        // Create message to be sent to ChildQueue
        _newChildren = new ChildArrivalMsg();

        // Generate _bulk children and add them to the message
        for (unsigned int i = 0; i < _bulk; ++i){
            double quitTime = _Q;
            _newChildren->addChild(quitTime);
        }

        // Send the message
        send(_newChildren, "toChildQueue");

        // Schedule next arrival
        scheduleAt(simTime()+_interarrivalTime, _nextArrival);
    }
}

void DummyChildPool::finish() {
    if (_nextArrival->isScheduled())
        cancelAndDelete(_nextArrival);
    else
        delete _nextArrival;
}
