/*
 * Project team:        Biondi, Cristofani, Guidotti
 * Academic Year:       2022/2023
 * File Description:    This is the file containing the implementation
 *                      for functions of the class Child.
 */

#include "Child.h"

// Initialize the static member variable for id assignment
int Child::_nextId = 1;

/**
 * Child's default constructor
 */
Child::Child(){}

/**
 * Child's constructor implementation
 *
 * @param _quitTime: represents the simtime at which the child will exit the queue
 */
Child::Child(SimTime _quitTime) :
    _id(_nextId++), _quitTime(_quitTime) {}

/**
 * Child's copy constructor implementation
 *
 * @param other: Child's instance reference, to be used for new instance construction
 */
Child::Child(const Child &other) :
    _id(other._id), _quitTime(other._quitTime){}

/**
 * Child's copy assignment operator implementation
 *
 * @param other: Child's instance reference, to be used for instance initialization
 */
Child& Child::operator=(const Child &other) {
    _id = other._id;
    _quitTime = other._quitTime;
    return *this;
}

/**
 * Child's equality operator
 *
 * @param other: Child's instance reference, to be used for comparison
 */
bool Child::operator==(const Child &other) const{
    return _id == other._id && _quitTime == other._quitTime;
}

/**
 * Get the value of the 'id' attribute
 */
int Child::getId() const{
    return _id;
}

/*
 * Get the value of the 'quitTime' attribute
 */
SimTime Child::getQuitTime() const{
    return _quitTime;
}
