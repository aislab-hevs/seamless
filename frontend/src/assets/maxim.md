## Features
MAXIM-GPRT is a multi-agent system (MAS) simulator. It allows to create a network of communicating agents in order to study scheduling and negotiation algorithms. The system is powered by Omnet++ simulation framework.

### Core
The core of the simulator is composed of the following modules:

- *Agent*
- *Scheduler*
- *Task*
- *MsgTask*
- *Server*
- *Service*
- *Need*
- *Bid*
- *NegSession*
- *AgentMSG*
- *Task Handler*
- *Service Handler*
- *Needs Handler*
- *Server Handler*
- *Session Handler*
- *Heuristic Handler*

#### Agent
The agent is the most important module of this simulator. The main functionalities of the agent are classified in three categories:

- Initialization and Finalization
- Message Handling
- Behaviors

##### Initialization and Finalization
Each module's parameters and fields need to be initialized when the simulation starts. Omnet++ offers a built-in function called `initialize()` that is called when the modules are created. It is important to note that this function is not automatically generated, thus the user must implement it according to the specific case. In MAXIM-GPRT, the initialize function creates the main components of each agent. It also creates a set of messages that each agent sends to self, in order to start the simulation. Since Omnet++ is a *discrete event simulation system*, each action is triggered by an event represented by a *message*. Each module can send messages to self, to trigger internal activities, or to other modules, to trigger interaction.

When an agent terminates, the simulator calls another built-in function called `finish()`. Differently from the initialization function, it is not mandatory to override this one, but it can be useful. In MAXIM-GPRT it is used to write down statistic results and to dispose pending messages (in case the simulation terminates without processing all the events in the Future Event Set - see [Omnet++ Event Loop](https://www.omnetpp.org/doc/omnetpp/manual/#sec:simple-modules:event-loop)).

##### Message Handling
As anticipated in the previous section, messages are used to trigger actions. Omnet++ provides the `handleMessage()` function that has to be defined to manage all the incoming messages and to react accordingly. In MAXIM-GPRT there are five functions that handle messages:

- `handleMessage()` : overrides the pre-defined function. It checks if the simulation is General Purpose (i.e. it uses algorithms that do not guarantee real time constraints) or in Real Time (i.e. it uses real-time compliant algorithms) and calls the respective function.
- `handleMessageGP()` : this function is called in case the simulation is General Purpose. This function checks the `informative` field of the message to extract its purpose. Next, it checks if the message is a self message. In that case, it triggers one of the following actions (that are explained in the **Behaviours** section):

    - Set taskset
    - Schedule task
    - Activate task
    - Check task termination
    - Check deadline miss
    - Publish services to the DF
    - Generate needs
    - Release need
    - Acknowledge task

  If the message comes from another agent, it can trigger one of the following actions:

  - `handle_ag_msg()` : handles messages in regular agents. It triggers one of the following actions:

    - Process list of potential contractors
    - Begin negotiation
    - Bid
    - Reject negotiation
    - Close negotiation
    - Refuse negotiation

  - `handle_df_msg()` : handles messages in the DF. It triggers one of the following actions:

    - Publish services
    - Request service

- `handleMessageRT()` : it triggers the same actions as `handleMessageGP()` with some differences:

    - Schedule task in Real-Time
    - Check task termination in Real-Time
    - Preempt Task (additional action)

    Furthermore, this function checks whether the `msg_server_mode` is active. In this case, each message directed to or coming from other agents is pre-processed by a dedicated CBS server (i.e. *read* server and *write* server).

##### Behaviors
Behaviors represent actions that agents can perform:

- `set_ag_taskset` : the agent's task handler loads the agent's knowledge from a JSON file. The knowledge represents the tasks that the agent can do and that are not necessarily scheduled.
- `schedule_taskset` : handles the scheduling process in a General Purpose simulation.
- `schedule_taskset_rt` : handles the scheduling process in a Real-Time simulation.
- `activate_task` : it activates a task whenever it's released. After activating the task, it schedules the check for completion.
- `check_task_completion` : checks if a task has completed its execution in a General Purpose simulation. If a task has terminated, this function removes it from the ready queue, schedules the activation of the next task, and writes statistic data concerning the response time and lateness (in case it missed its deadline) of the completed task.
- `check_task_completion_rt` : checks if a task has completed its execution in a Real Time simulation. If a task has terminated, this function removes it from the ready queue, schedules the activation of the next task, and writes data concerning the response time of the completed task. It also handles the check for completion of sporadic tasks through servers.
- `preempt` : handles the tasks' preemption.
- `check_ddl_miss` : check whether a task missed its deadline. In that case it writes the event in the deadline miss report file.
- `publish services` : sends to the DF a list with all the public tasks of the agent.
- `generate_ag_needs` : loads the agent's needs from a JSON file. A need is a request that the agent does at some time for some service(s).
- `release_need` : releases a scheduled need and creates a request to send to the DF.
- `process_list` : retrieves the list of possible contractors for a specific service and sends a call for proposal to one or more of them according to a specific selection heuristic (i.e. first, random or random subset). It also schedules the acknowledgment of the job to a time equal to a set negotiation time window.
- `begin_neg` : begins the negotiation of a service. The agent decides to bid for a service according to the negotiation protocol's policy (i.e. if the conditions are positive, the agent makes the bid).
- `receive_bid` : the agent collects all the bids arrived during the negotiation time window. If a bid arrives too late, the agents automatically refuses the proposal.
- `reject` : the contractor agent rejects a bid if it is already busy in another negotiation session.
- `acknowledge_job` : the agent evaluates all the offers that arrived from the contractors during the negotiation time window. It then selects one contractor according to a specific selection heuristic.
- `close` : the acknowledged agent copies the requested task in its release queue and proceeds with its execution.
- `df_publish` : this action is only performed by the DF. It records all the services offered by an agent.
- `df_request` : this action is only performed by the DF. It prepares a list of possible contractors for a specific service and sends it back to the agent that requested it.

#### Scheduler
The scheduler component provides all the functionalities to implement the agent's *internal* scheduler (it is important to note that the scheduler is intended as _scheduler for tasks **inside** the agent_ and not _**among**_ agents). It contains three main structures:

- *release queue* : contains the tasks to release
- *ready queue* : contains the tasks ready to execute
- *pending tasks queue* : contains the tasks undergoing negotiation

In addition to providing the main functionalities to manipulate these structures, this module offers the following features:

- *Schedulability test* : this feature allows to test a task-set and check if it is schedulable or not according to EDF. This test is based on the notion of utilization factor (see [Earliest Deadline First](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling))
- *Check negotiation policy* : this feature allows to evaluate if the agent can bid for a job, according to a negotiation policy:

  - `check_cnet` : this function tells if the agent can make a bid according to the Contract Net protocol. In this case, the conditions to make a bid are that the agent is able to do the task and that it is not already busy negotiating another service. If these two conditions hold, then the agent is able to make a bid.
  - `check_rbn` : this function tells if the agent can make a bid according to the Reservation Based Negotiation protocol. With the RBN protocol, each agent is able to tell if it can *reserve* a part of its *utilization factor* to perform requested services. This means that this test relies both on the schedulability test and on the ability to evaluate the consequences of the negotiation on the future task-set. To perform this test, the scheduler needs to evaluate a *potential task-set* that would be the result of the negotiation. For this purpose, this method performs three actions:

    - `eval_current_taskset` : the scheduler creates a snapshot of the current task-set in order to calculate the utilization factor. This method takes as an input the time window of the service undergoing negotiation. It examines the release queue and the ready queue taking all the tasks that fall into that specific time window (without repetition).
    - `eval_pending_taskset` : the scheduler creates a pending task-set taking the services undergoing negotiation.
    - `eval_taskset` : this method merges the results of the previous ones to create a potential task-set.

  - `check_rbn_plus` : this function performs the check for the RBN+ algorithm. Like the normal RBN, it checks if the agent has enough bandwidth to perform the requested task, but in addition it also checks if it can execute the task in compliance with additional requested parameters. With RBN+ the negotiation includes a minimum and a maximum period within the which the task needs to be executed. If the participator agent(s) cannot perform the task within this frame, they make an offer with a slightly worse period, and the negotiation goes until the initiator is happy with the offer or rejects it (this is called *Reservation Based Negotiation with Performance Degradation*).

    Once the potential task-set has been created, the scheduler performs a schedulability test to obtain a potential utilization factor. If this one is below the utilization threshold (i.e. utilization upper bound), then the agent makes a bid. Otherwise, it rejects the proposal.

#### Task
The task is characterized by the following parameters:

- *Id*
- *Executor* : contains the id of the agent executing the task
- *Demander* : contains the id of the agent that demanded the tasks
- *Computation time* : it represents the _**Worst Case Execution Time**_ (_**WCET**_) of the task
- *Residual computation time* : it represents the time that the task needs to complete its execution
- *Arrival time* : time at which the task is released
- *Deadline* : represents the relative deadline of the task
- *Period* : it is the time interval after the which another instance of the same task is released
- *First activation* : contains the time value at which the task has been activated for the first time
- *Last activation* : contains the time value at which the task has been activated for the last time (e.g. before being preempted)
- *Server* : contains the id of the associated server, in case the task is sporadic.
- *Number of executions* : the value of this field tells how many instances of the task will be executed (if the value is -1 there will be virtually infinite instances of the task)
- *Public* : this field tells if the task is public (it is exposed as a service)

#### Message Task
This class extends the Task class and represents the activity of reading or writing a message. This special task has an additional field containing the *message* to process. This class is used simulate the handling of reading and writing activities as sporadic tasks (CBS).

#### Server
This class extends the Task class and represents CBS servers. Each server executes sporadic tasks and is characterized by:

- *Budget* : it represents the computational time that the tasks in the server can use.
- *Period*
- *Bandwidth* : represents the utilization of the server. It is given by the budget divided by the period.
- *Queue* : contains all the sporadic tasks that need to be executed.

#### Service
The Service class identifies services through two fields:

- *Id* : id of the agent offering the service
- *Task id* : id of the offered task

Services are handled by the Directory Facilitator.

#### Need
As anticipated, a need represents a request for a service. The Need class is characterized by the following parameters:

- *Need id* : unique need identifier
- *Need release time* : time at which the need is released
- *Needed tasks ids* : contains the ids of the needed tasks. One need can represent a request for one or more tasks at once
- *Needed release time* : this value indicates the release time of the needed task(s)
- *Needed end time* : this value indicates the deadline of the needed task(s)
- *Needed number of executions* : this value indicates the number of executions of the 
needed task(s)
- *Needed minimum/maximum task period* : this values represent the minimum and maximum period requested for the neeeded task when using RBN+.

#### Bid
This class represents a bid for a service. It contains two paramenters:

- *Contractor* : id of the bidder
- *Offer* : double value corresponding to the offer (the structure of the bid can be changed according to the nature of the service)

#### Negotiation Session
This class represents a Negotiation Session for a specific need. Each session is identified by a need's parameters (need id, needed release time and needed end time). The session also contains all the bids received for a service.

#### AgentMSG
This class represents a user defined type of message (see [Omnet++ Message Definitions](https://www.omnetpp.org/doc/omnetpp/manual/#cha:msg-def)). It is characterized by the following parameters:

- *Source* : id of the sender agent
- *Destination* : id of the receiver agent
- *Informative* : it represents the purpose of the message. The message will trigger a specific action according to the value of this field
- *Task parameters* : the message can carry task parameters as the id, release time, and so on
- *Need Parameters* : as above

#### Handlers
Handlers are helper classes that allow to manipulate the respective objects:

- `TaskHandler` : it provides methods to clone tasks and read tasks from an XML file.
- `ServiceHandler` : it provides methods to create, clone, add and remove services and retrieve the list of agents offering a particular service.
- `NeedsHandler` : it contains all the needs of an agent. It provides a method to load a set of needs from an XML file.
- `ServerHandler` : it provides functionalities to handle CBS servers.
- `SessionHandler` : it provides methods to handle negotiation sessions.
- `HeuristicHandler` : it provides methods to implement selection heuristics. These functions are used to select contractors and bidders.

### Utilities
The Utilities are helper components that contain support methods:

- `Ag_settings` : it provides methods to create and consult the connections table of the agents populating the network (i.e. the mapping between gates and agents).
- `Writer` : it provides methods to write statistic data about the simulation in the respective JSON files. It is possible to record information about deadline miss, lateness, and response time.
