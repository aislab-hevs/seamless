//
// Generated file, do not edit! Created by nedtool 5.5 from src/agentMSG.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "agentMSG_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(agentMSG)

agentMSG::agentMSG(const char *name, short kind) : ::omnetpp::cMessage(name,kind)
{
    this->source = 0;
    this->destination = 0;
    this->hopCount = 0;
    this->informative = 0;
    this->ag_id = 0;
    this->ag_task_id = 0;
    this->ag_task_demander = 0;
    this->ag_task_server = 0;
    this->ag_task_t_finito = 0;
    this->ag_task_release_time = 0;
    this->ag_task_ddl = 0;
    this->replenish = 0;
    this->content = 0;
    this->neg_step = 0;
    this->round = 0;
    this->bid = 0;
    this->utilization = -1;
    this->processed = false;
}

agentMSG::agentMSG(const agentMSG& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

agentMSG::~agentMSG()
{
}

agentMSG& agentMSG::operator=(const agentMSG& other)
{
    if (this==&other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void agentMSG::copy(const agentMSG& other)
{
    this->source = other.source;
    this->destination = other.destination;
    this->hopCount = other.hopCount;
    this->informative = other.informative;
    this->ag_id = other.ag_id;
    this->ag_task_id = other.ag_task_id;
    this->ag_task_demander = other.ag_task_demander;
    this->ag_task_server = other.ag_task_server;
    this->ag_task_t_finito = other.ag_task_t_finito;
    this->ag_task_release_time = other.ag_task_release_time;
    this->ag_task_ddl = other.ag_task_ddl;
    this->replenish = other.replenish;
    this->need = other.need;
    this->ag_needed_tasks = other.ag_needed_tasks;
    this->agents_per_need = other.agents_per_need;
    this->public_tasks = other.public_tasks;
    this->content = other.content;
    this->neg_step = other.neg_step;
    this->round = other.round;
    this->bid = other.bid;
    this->utilization = other.utilization;
    this->processed = other.processed;
}

void agentMSG::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->source);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->informative);
    doParsimPacking(b,this->ag_id);
    doParsimPacking(b,this->ag_task_id);
    doParsimPacking(b,this->ag_task_demander);
    doParsimPacking(b,this->ag_task_server);
    doParsimPacking(b,this->ag_task_t_finito);
    doParsimPacking(b,this->ag_task_release_time);
    doParsimPacking(b,this->ag_task_ddl);
    doParsimPacking(b,this->replenish);
    doParsimPacking(b,this->need);
    doParsimPacking(b,this->ag_needed_tasks);
    doParsimPacking(b,this->agents_per_need);
    doParsimPacking(b,this->public_tasks);
    doParsimPacking(b,this->content);
    doParsimPacking(b,this->neg_step);
    doParsimPacking(b,this->round);
    doParsimPacking(b,this->bid);
    doParsimPacking(b,this->utilization);
    doParsimPacking(b,this->processed);
}

void agentMSG::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->source);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->informative);
    doParsimUnpacking(b,this->ag_id);
    doParsimUnpacking(b,this->ag_task_id);
    doParsimUnpacking(b,this->ag_task_demander);
    doParsimUnpacking(b,this->ag_task_server);
    doParsimUnpacking(b,this->ag_task_t_finito);
    doParsimUnpacking(b,this->ag_task_release_time);
    doParsimUnpacking(b,this->ag_task_ddl);
    doParsimUnpacking(b,this->replenish);
    doParsimUnpacking(b,this->need);
    doParsimUnpacking(b,this->ag_needed_tasks);
    doParsimUnpacking(b,this->agents_per_need);
    doParsimUnpacking(b,this->public_tasks);
    doParsimUnpacking(b,this->content);
    doParsimUnpacking(b,this->neg_step);
    doParsimUnpacking(b,this->round);
    doParsimUnpacking(b,this->bid);
    doParsimUnpacking(b,this->utilization);
    doParsimUnpacking(b,this->processed);
}

int agentMSG::getSource() const
{
    return this->source;
}

void agentMSG::setSource(int source)
{
    this->source = source;
}

int agentMSG::getDestination() const
{
    return this->destination;
}

void agentMSG::setDestination(int destination)
{
    this->destination = destination;
}

int agentMSG::getHopCount() const
{
    return this->hopCount;
}

void agentMSG::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

int agentMSG::getInformative() const
{
    return this->informative;
}

void agentMSG::setInformative(int informative)
{
    this->informative = informative;
}

int agentMSG::getAg_id() const
{
    return this->ag_id;
}

void agentMSG::setAg_id(int ag_id)
{
    this->ag_id = ag_id;
}

int agentMSG::getAg_task_id() const
{
    return this->ag_task_id;
}

void agentMSG::setAg_task_id(int ag_task_id)
{
    this->ag_task_id = ag_task_id;
}

int agentMSG::getAg_task_demander() const
{
    return this->ag_task_demander;
}

void agentMSG::setAg_task_demander(int ag_task_demander)
{
    this->ag_task_demander = ag_task_demander;
}

int agentMSG::getAg_task_server() const
{
    return this->ag_task_server;
}

void agentMSG::setAg_task_server(int ag_task_server)
{
    this->ag_task_server = ag_task_server;
}

double agentMSG::getAg_task_t_finito() const
{
    return this->ag_task_t_finito;
}

void agentMSG::setAg_task_t_finito(double ag_task_t_finito)
{
    this->ag_task_t_finito = ag_task_t_finito;
}

double agentMSG::getAg_task_release_time() const
{
    return this->ag_task_release_time;
}

void agentMSG::setAg_task_release_time(double ag_task_release_time)
{
    this->ag_task_release_time = ag_task_release_time;
}

double agentMSG::getAg_task_ddl() const
{
    return this->ag_task_ddl;
}

void agentMSG::setAg_task_ddl(double ag_task_ddl)
{
    this->ag_task_ddl = ag_task_ddl;
}

double agentMSG::getReplenish() const
{
    return this->replenish;
}

void agentMSG::setReplenish(double replenish)
{
    this->replenish = replenish;
}

NeedPtr& agentMSG::getNeed()
{
    return this->need;
}

void agentMSG::setNeed(const NeedPtr& need)
{
    this->need = need;
}

IntVector& agentMSG::getAg_needed_tasks()
{
    return this->ag_needed_tasks;
}

void agentMSG::setAg_needed_tasks(const IntVector& ag_needed_tasks)
{
    this->ag_needed_tasks = ag_needed_tasks;
}

IntVector& agentMSG::getAgents_per_need()
{
    return this->agents_per_need;
}

void agentMSG::setAgents_per_need(const IntVector& agents_per_need)
{
    this->agents_per_need = agents_per_need;
}

IntVector& agentMSG::getPublic_tasks()
{
    return this->public_tasks;
}

void agentMSG::setPublic_tasks(const IntVector& public_tasks)
{
    this->public_tasks = public_tasks;
}

int agentMSG::getContent() const
{
    return this->content;
}

void agentMSG::setContent(int content)
{
    this->content = content;
}

int agentMSG::getNeg_step() const
{
    return this->neg_step;
}

void agentMSG::setNeg_step(int neg_step)
{
    this->neg_step = neg_step;
}

int agentMSG::getRound() const
{
    return this->round;
}

void agentMSG::setRound(int round)
{
    this->round = round;
}

double agentMSG::getBid() const
{
    return this->bid;
}

void agentMSG::setBid(double bid)
{
    this->bid = bid;
}

double agentMSG::getUtilization() const
{
    return this->utilization;
}

void agentMSG::setUtilization(double utilization)
{
    this->utilization = utilization;
}

bool agentMSG::getProcessed() const
{
    return this->processed;
}

void agentMSG::setProcessed(bool processed)
{
    this->processed = processed;
}

class agentMSGDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    agentMSGDescriptor();
    virtual ~agentMSGDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(agentMSGDescriptor)

agentMSGDescriptor::agentMSGDescriptor() : omnetpp::cClassDescriptor("agentMSG", "omnetpp::cMessage")
{
    propertynames = nullptr;
}

agentMSGDescriptor::~agentMSGDescriptor()
{
    delete[] propertynames;
}

bool agentMSGDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<agentMSG *>(obj)!=nullptr;
}

const char **agentMSGDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *agentMSGDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int agentMSGDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 22+basedesc->getFieldCount() : 22;
}

unsigned int agentMSGDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<22) ? fieldTypeFlags[field] : 0;
}

const char *agentMSGDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "source",
        "destination",
        "hopCount",
        "informative",
        "ag_id",
        "ag_task_id",
        "ag_task_demander",
        "ag_task_server",
        "ag_task_t_finito",
        "ag_task_release_time",
        "ag_task_ddl",
        "replenish",
        "need",
        "ag_needed_tasks",
        "agents_per_need",
        "public_tasks",
        "content",
        "neg_step",
        "round",
        "bid",
        "utilization",
        "processed",
    };
    return (field>=0 && field<22) ? fieldNames[field] : nullptr;
}

int agentMSGDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+2;
    if (fieldName[0]=='i' && strcmp(fieldName, "informative")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_id")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_task_id")==0) return base+5;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_task_demander")==0) return base+6;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_task_server")==0) return base+7;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_task_t_finito")==0) return base+8;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_task_release_time")==0) return base+9;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_task_ddl")==0) return base+10;
    if (fieldName[0]=='r' && strcmp(fieldName, "replenish")==0) return base+11;
    if (fieldName[0]=='n' && strcmp(fieldName, "need")==0) return base+12;
    if (fieldName[0]=='a' && strcmp(fieldName, "ag_needed_tasks")==0) return base+13;
    if (fieldName[0]=='a' && strcmp(fieldName, "agents_per_need")==0) return base+14;
    if (fieldName[0]=='p' && strcmp(fieldName, "public_tasks")==0) return base+15;
    if (fieldName[0]=='c' && strcmp(fieldName, "content")==0) return base+16;
    if (fieldName[0]=='n' && strcmp(fieldName, "neg_step")==0) return base+17;
    if (fieldName[0]=='r' && strcmp(fieldName, "round")==0) return base+18;
    if (fieldName[0]=='b' && strcmp(fieldName, "bid")==0) return base+19;
    if (fieldName[0]=='u' && strcmp(fieldName, "utilization")==0) return base+20;
    if (fieldName[0]=='p' && strcmp(fieldName, "processed")==0) return base+21;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *agentMSGDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "double",
        "double",
        "double",
        "double",
        "NeedPtr",
        "IntVector",
        "IntVector",
        "IntVector",
        "int",
        "int",
        "int",
        "double",
        "double",
        "bool",
    };
    return (field>=0 && field<22) ? fieldTypeStrings[field] : nullptr;
}

const char **agentMSGDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *agentMSGDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int agentMSGDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    agentMSG *pp = (agentMSG *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *agentMSGDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    agentMSG *pp = (agentMSG *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string agentMSGDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    agentMSG *pp = (agentMSG *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSource());
        case 1: return long2string(pp->getDestination());
        case 2: return long2string(pp->getHopCount());
        case 3: return long2string(pp->getInformative());
        case 4: return long2string(pp->getAg_id());
        case 5: return long2string(pp->getAg_task_id());
        case 6: return long2string(pp->getAg_task_demander());
        case 7: return long2string(pp->getAg_task_server());
        case 8: return double2string(pp->getAg_task_t_finito());
        case 9: return double2string(pp->getAg_task_release_time());
        case 10: return double2string(pp->getAg_task_ddl());
        case 11: return double2string(pp->getReplenish());
        case 12: {std::stringstream out; out << pp->getNeed(); return out.str();}
        case 13: {std::stringstream out; out << pp->getAg_needed_tasks(); return out.str();}
        case 14: {std::stringstream out; out << pp->getAgents_per_need(); return out.str();}
        case 15: {std::stringstream out; out << pp->getPublic_tasks(); return out.str();}
        case 16: return long2string(pp->getContent());
        case 17: return long2string(pp->getNeg_step());
        case 18: return long2string(pp->getRound());
        case 19: return double2string(pp->getBid());
        case 20: return double2string(pp->getUtilization());
        case 21: return bool2string(pp->getProcessed());
        default: return "";
    }
}

bool agentMSGDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    agentMSG *pp = (agentMSG *)object; (void)pp;
    switch (field) {
        case 0: pp->setSource(string2long(value)); return true;
        case 1: pp->setDestination(string2long(value)); return true;
        case 2: pp->setHopCount(string2long(value)); return true;
        case 3: pp->setInformative(string2long(value)); return true;
        case 4: pp->setAg_id(string2long(value)); return true;
        case 5: pp->setAg_task_id(string2long(value)); return true;
        case 6: pp->setAg_task_demander(string2long(value)); return true;
        case 7: pp->setAg_task_server(string2long(value)); return true;
        case 8: pp->setAg_task_t_finito(string2double(value)); return true;
        case 9: pp->setAg_task_release_time(string2double(value)); return true;
        case 10: pp->setAg_task_ddl(string2double(value)); return true;
        case 11: pp->setReplenish(string2double(value)); return true;
        case 16: pp->setContent(string2long(value)); return true;
        case 17: pp->setNeg_step(string2long(value)); return true;
        case 18: pp->setRound(string2long(value)); return true;
        case 19: pp->setBid(string2double(value)); return true;
        case 20: pp->setUtilization(string2double(value)); return true;
        case 21: pp->setProcessed(string2bool(value)); return true;
        default: return false;
    }
}

const char *agentMSGDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 12: return omnetpp::opp_typename(typeid(NeedPtr));
        case 13: return omnetpp::opp_typename(typeid(IntVector));
        case 14: return omnetpp::opp_typename(typeid(IntVector));
        case 15: return omnetpp::opp_typename(typeid(IntVector));
        default: return nullptr;
    };
}

void *agentMSGDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    agentMSG *pp = (agentMSG *)object; (void)pp;
    switch (field) {
        case 12: return (void *)(&pp->getNeed()); break;
        case 13: return (void *)(&pp->getAg_needed_tasks()); break;
        case 14: return (void *)(&pp->getAgents_per_need()); break;
        case 15: return (void *)(&pp->getPublic_tasks()); break;
        default: return nullptr;
    }
}


