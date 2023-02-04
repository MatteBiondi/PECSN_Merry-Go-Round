/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the file containing the definition
 *                      for functions and attributes of the class
 *                      ChildArrivalMsg. This class represents the
 *                      message containing the arrived children.
 */

#ifndef CHILDARRIVALMSG_H_
#define CHILDARRIVALMSG_H_

#include <vector>
#include <omnetpp.h>
#include "Child.h"
#include "utility.h"

using namespace omnetpp;
using namespace std;

class ChildArrivalMsg: public cMessage {
private:
    std::vector<Child> _children;

public:
    // Constructor
    ChildArrivalMsg(const char* name = CHILD_ARRIVAL, short kind = 0);

    // Create and add a child to the vector
    void addChild(SimTime quitTime);

    // Get the number of children in the vector
    int getNumChildren() const;

    // Get a child from the vector
    Child getChild(int index) const;
};

#endif /* CHILDARRIVALMSG_H_ */
