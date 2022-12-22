/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the file containing the implementation
 *                      for functions of the class Child.
 */

#include "Child.h"

// Initialize the static member variable
int Child::_nextId = 1;

// Constructor implementation
Child::Child(double _quitTime) :
    _id(_nextId++), _quitTime(_quitTime) {}

// Copy constructor implementation
Child::Child(const Child &other) :
    _id(other._id), _quitTime(other._quitTime){}

// Copy assignment operator implementation
Child& Child::operator=(const Child &other) {
    _id = other._id;
    _quitTime = other._quitTime;
    return *this;
}

// Equality operator
bool Child::operator==(const Child &other) const{
    return _id == other._id && _quitTime == other._quitTime;
}

// Get the value of the 'id' attribute
int Child::getId() const{
    return _id;
}

// Get the value of the 'quitTime' attribute
double Child::getQuitTime() const{
    return _quitTime;
}
