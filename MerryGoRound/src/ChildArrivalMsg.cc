/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the file containing the implementation
 *                      for functions of the class ChildArrivalMsg.
 */

#include "ChildArrivalMsg.h"

/**
 * ChildArrivalMsg's constructor. The message priority is set to 0
 *
 * @param name: message name ('ChildArrivalMsg' as default value)
 * @param kind: message kind (0 as default value)
 */
ChildArrivalMsg::ChildArrivalMsg(const char* name, short kind) : cMessage(name, kind){
    setSchedulingPriority(HIGH_PRIORITY);
};

/**
 * Create and add a Child to the vector
 *
 * @param quitTime: represents the simtime at which the child will exit the queue
 */
void ChildArrivalMsg::addChild(SimTime quitTime){
    _children.emplace_back(quitTime);
}

/**
 * Get the number of children in the vector
 */
int ChildArrivalMsg::getNumChildren() const{
    return _children.size();
}

/**
 * Get a child from the vector
 *
 * @param index: vector index to be accessed
 */
Child ChildArrivalMsg::getChild(int index) const{
    return _children[index];
}

