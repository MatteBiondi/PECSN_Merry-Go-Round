//
// Generated file, do not edit! Created by opp_msgtool 6.0 from RemoveFromQueueMsg.msg.
//

#ifndef __REMOVEFROMQUEUEMSG_M_H
#define __REMOVEFROMQUEUEMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class RemoveFromQueueMsg;
/**
 * Class generated from <tt>RemoveFromQueueMsg.msg:1</tt> by opp_msgtool.
 * <pre>
 * message RemoveFromQueueMsg
 * {
 *     int howMany;
 * }
 * </pre>
 */
class RemoveFromQueueMsg : public ::omnetpp::cMessage
{
  protected:
    int howMany = 0;

  private:
    void copy(const RemoveFromQueueMsg& other);

  protected:
    bool operator==(const RemoveFromQueueMsg&) = delete;

  public:
    RemoveFromQueueMsg(const char *name=nullptr, short kind=0);
    RemoveFromQueueMsg(const RemoveFromQueueMsg& other);
    virtual ~RemoveFromQueueMsg();
    RemoveFromQueueMsg& operator=(const RemoveFromQueueMsg& other);
    virtual RemoveFromQueueMsg *dup() const override {return new RemoveFromQueueMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getHowMany() const;
    virtual void setHowMany(int howMany);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const RemoveFromQueueMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, RemoveFromQueueMsg& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline RemoveFromQueueMsg *fromAnyPtr(any_ptr ptr) { return check_and_cast<RemoveFromQueueMsg*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __REMOVEFROMQUEUEMSG_M_H

