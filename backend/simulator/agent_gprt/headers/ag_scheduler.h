/*
 * ag_Scheduler.h
 *
 *  Created on: 25 set 2017
 *      Author: peppe
 */

#ifndef HEADERS_AG_SCHEDULER_H_
#define HEADERS_AG_SCHEDULER_H_

#include <stdio.h>
#include <string.h>
#include <vector>
#include <omnetpp.h>
#include <algorithm>

#include "ag_settings.h"
#include "agentMSG_m.h"
#include "task.h"
#include "server.h"
#include "server_handler.h"

using namespace std;

//custom type that defines what kind of scheduler is in use
//(this is more for code clarity than functionality)
enum SchedType {
    FCFS, RR, EDF, SJF, RM,
};

class Ag_Scheduler {

public:
    //Release time sensitivity (epsilon between task release time and simulation time)
    const double EPSILON = 0.05;

    Ag_Scheduler(SchedType type);
    ~Ag_Scheduler();

    /**
     Creates the scheduler for a given set of tasks

     @param vector<Task*> contains the tasks to be scheduled
     @return a boolean that states if the operation was successful
     */
    bool ag_create_scheduler(vector<Task*>);

    /**
     Implements the schedulability test (not used in non-RT algorithms)

     @param vector<Task*> contains the taskset to test
     @return the value of the utilization factor
     */
    double ag_sched_test(vector<Task*>, ServerHandler* server_handler = nullptr);

    vector<Task*> eval_taskset(double, double);

    bool check_overlap(double, double, double, double);

    /**
     Sorts the taskset according to the tasks' arrival time
     */
    void ag_sort_tasks_arrival();
    void ag_sort_tasks_ready(double c_res = 0);
    void ag_sort_tasks_ddl(double);
    void ag_sort_tasks_period(double);
    void ag_sort_tasks_comp_time();
    /**
     Calculates the utilization factor
     */
    void ag_calculate_current_UF();

    /**
     Calculates the potential utilization factor
     */
    void ag_calculate_potential_UF();

    /**
     Returns true if a single task has arrived
     */
    bool ag_task_arrived(Task* server = nullptr);

    /**
     Adds a task in the vector that contains the tasks to be released

     @param Task *pn_task pointer to the task to add
     */
    void ag_add_task_in_vector_to_release(Task* pn_task);
    void ag_replace_task_to_release(Task*);
    void ag_add_pending_task(Task*);

    /**
     Adds a task in the vector that contains the ready tasks

     @param Task *pn_task pointer to the task to add
     */
    void ag_add_task_in_ready_tasks_vector(Task* pn_task);

    /**
     Removes the first element in the ready tasks vector
     */
    void ag_remove_head_in_ready_tasks_vector();

    /**
     Removes a task in the ready vector (not used)

     @param int id is the identifier of the task to be removed
     */
    void ag_remove_task_in_ready(int id);
    void ag_remove_task_to_release(int id);
    void ag_remove_pending_task(int id);

    /**
     Updates the active task in the vector containing sorted tasks

     @param Task *p_task pointer to the task to update
     */
    void update_active_task_in_sorted_tasks_vector(Task *p_task);

    //getter methods

    /**
     Returns the vector containing the tasks to release
     */
    vector<Task*> get_tasks_vector_to_release();

    /**
     Returns the vector containing the ready tasks
     */
    vector<Task*> get_tasks_vector_ready();
    vector<Task*> get_pending_tasks_vector();

    /**
     Returns the scheduler's type (i.e. the scheduling algorithm)
     */
    SchedType get_sched_type();

    /**
     Returns the time quantum (set as a constant)
     */
    double get_quantum();

    /**
     Returns the residual computation time when a deadline miss occurs

     @param Task *msg_task pointer to the task that sent the message to check the deadline miss
     @param int first_task_id identifier of the first task in the ready vector
     */
    double get_ddl_miss(Task *msg_task, int first_task_id);

    /**
     Returns a ready task according to its id and release time

     @param int task_id identifier of the task to find
     @param double task_release contains the task's release time
     */
    Task* get_ready_task_by_id(int task_id, int task_demander, double task_release);

    // debug methods

    /**
     Prints the tasks to release
     */
    void ev_ag_tasks_vector_to_release();

    /**
     Prints the ready tasks
     */
    void ev_ag_tasks_vector_ready();

    /**
     Negotiation related
     */
    bool check_cnet(int, bool&, Need*);
    bool check_rbn(int, ServerHandler*, Need*, double msg_util = 0);
    bool check_rbn_plus(int, double&, double&, ServerHandler*, Need*, double msg_util = 0);
    double get_current_util(ServerHandler*, double msg_util = 0);

private:
    //RR quantum
    const double RR_QUANTUM = 3;

    SchedType type;
    double quantum;
    double agCurrentUF;
    double agPotentialUF;
    vector<Task*> ag_tasks_vector;
    vector<Task*> ag_tasks_vector_to_release;
    vector<Task*> ag_tasks_vector_ready;
    vector<Task*> ag_pending_tasks;

    //helper methods to estimate future taskset
    vector<Task*> eval_current_taskset(double, double);
    void eval_pending_taskset(vector<Task*>&);
};



#endif /* HEADERS_AG_SCHEDULER_H_ */

