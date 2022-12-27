/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is an header file containing declarations
 *                      for functions and attributes of the class Child.
 *                      The inclusion of this file in ".cc" file for the
 *                      implementation is needed
 */

#ifndef CHILD_H_
#define CHILD_H_

#include <omnetpp.h>

using namespace omnetpp;
using namespace std;

class Child {
public:
    // Default constructor
    Child();

    // Constructor
    Child(SimTime _quitTime);

    // Copy constructor
    Child(const Child &other);

    // Copy assignment operator
    Child& operator=(const Child &other);

    // Equality operator
    bool operator==(const Child &other) const;

    // Get the value of the 'id' attribute
    int getId() const;

    // Get the value of the 'quitTime' attribute
    SimTime getQuitTime() const;

private:
    static int _nextId;
    int _id;
    SimTime _quitTime;
};

#endif /* CHILD_H_ */
