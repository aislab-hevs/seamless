//
// Generated file, do not edit! Created by nedtool 5.5 from src/agentMSG.msg.
//

#ifndef __AGENTMSG_M_H
#define __AGENTMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0505
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
   #include <vector>
   #include "../headers/ag_need.h"
   
   typedef std::vector<int> IntVector;
   typedef Need *NeedPtr;
// }}

/**
 * Class generated from <tt>src/agentMSG.msg:13</tt> by nedtool.
 * <pre>
 * message agentMSG
 * {
 *     int source = 0;
 *     int destination = 0;
 *     int hopCount = 0;
 * 
 *     int informative = 0;
 * 
 *     // scheduler related
 *     //TODO: semplificare come per i need
 *     int ag_id = 0;
 *     int ag_task_id = 0;
 *     int ag_task_demander = 0;
 *     int ag_task_server = 0;
 *     double ag_task_t_finito = 0;
 *     double ag_task_release_time = 0;
 *     double ag_task_ddl = 0;
 *     double replenish = 0;
 *     // needs and services
 *     NeedPtr need;
 *     IntVector ag_needed_tasks;
 *     IntVector agents_per_need;
 *     IntVector public_tasks;
 * 
 *     // negotiation related
 *     int content = 0;
 *     int neg_step = 0;
 *     int round = 0;
 *     double bid = 0;
 *     double utilization = -1;
 *     bool processed = false;
 * }
 * </pre>
 */
class agentMSG : public ::omnetpp::cMessage
{
  protected:
    int source;
    int destination;
    int hopCount;
    int informative;
    int ag_id;
    int ag_task_id;
    int ag_task_demander;
    int ag_task_server;
    double ag_task_t_finito;
    double ag_task_release_time;
    double ag_task_ddl;
    double replenish;
    NeedPtr need;
    IntVector ag_needed_tasks;
    IntVector agents_per_need;
    IntVector public_tasks;
    int content;
    int neg_step;
    int round;
    double bid;
    double utilization;
    bool processed;

  private:
    void copy(const agentMSG& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const agentMSG&);

  public:
    agentMSG(const char *name=nullptr, short kind=0);
    agentMSG(const agentMSG& other);
    virtual ~agentMSG();
    agentMSG& operator=(const agentMSG& other);
    virtual agentMSG *dup() const override {return new agentMSG(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getSource() const;
    virtual void setSource(int source);
    virtual int getDestination() const;
    virtual void setDestination(int destination);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual int getInformative() const;
    virtual void setInformative(int informative);
    virtual int getAg_id() const;
    virtual void setAg_id(int ag_id);
    virtual int getAg_task_id() const;
    virtual void setAg_task_id(int ag_task_id);
    virtual int getAg_task_demander() const;
    virtual void setAg_task_demander(int ag_task_demander);
    virtual int getAg_task_server() const;
    virtual void setAg_task_server(int ag_task_server);
    virtual double getAg_task_t_finito() const;
    virtual void setAg_task_t_finito(double ag_task_t_finito);
    virtual double getAg_task_release_time() const;
    virtual void setAg_task_release_time(double ag_task_release_time);
    virtual double getAg_task_ddl() const;
    virtual void setAg_task_ddl(double ag_task_ddl);
    virtual double getReplenish() const;
    virtual void setReplenish(double replenish);
    virtual NeedPtr& getNeed();
    virtual const NeedPtr& getNeed() const {return const_cast<agentMSG*>(this)->getNeed();}
    virtual void setNeed(const NeedPtr& need);
    virtual IntVector& getAg_needed_tasks();
    virtual const IntVector& getAg_needed_tasks() const {return const_cast<agentMSG*>(this)->getAg_needed_tasks();}
    virtual void setAg_needed_tasks(const IntVector& ag_needed_tasks);
    virtual IntVector& getAgents_per_need();
    virtual const IntVector& getAgents_per_need() const {return const_cast<agentMSG*>(this)->getAgents_per_need();}
    virtual void setAgents_per_need(const IntVector& agents_per_need);
    virtual IntVector& getPublic_tasks();
    virtual const IntVector& getPublic_tasks() const {return const_cast<agentMSG*>(this)->getPublic_tasks();}
    virtual void setPublic_tasks(const IntVector& public_tasks);
    virtual int getContent() const;
    virtual void setContent(int content);
    virtual int getNeg_step() const;
    virtual void setNeg_step(int neg_step);
    virtual int getRound() const;
    virtual void setRound(int round);
    virtual double getBid() const;
    virtual void setBid(double bid);
    virtual double getUtilization() const;
    virtual void setUtilization(double utilization);
    virtual bool getProcessed() const;
    virtual void setProcessed(bool processed);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const agentMSG& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, agentMSG& obj) {obj.parsimUnpack(b);}


#endif // ifndef __AGENTMSG_M_H

