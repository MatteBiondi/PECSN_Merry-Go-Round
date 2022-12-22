/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the file containing the implementation
 *                      for functions of the class ChildArrivalMsg.
 */

#include "ChildArrivalMsg.h"

// Constructor
ChildArrivalMsg::ChildArrivalMsg(const char* name, short kind) : cMessage(name, kind){
    setSchedulingPriority(HIGH_PRIORITY);
};

// Create and add a child to the vector
void ChildArrivalMsg::addChild(double quitTime){
    _children.emplace_back(quitTime);
}

// Get the number of children in the vector
int ChildArrivalMsg::getNumChildren() const{
    return _children.size();
}

// Get a child from the vector
Child ChildArrivalMsg::getChild(int index) const{
    return _children[index];
}

