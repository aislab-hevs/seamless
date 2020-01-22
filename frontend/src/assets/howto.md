### INTRODUCTION
In safety-critical scenarios, compliance with strict-timing constraints is mandatory. The SEAMLESS project enables the simulation and analysis of the behaviors produced by Multi-Agent Systems (MAS) powered by both General-Purpose (GP) and Real-time (RT) algorithms. Therefore, SEAMLESS is a crucial tool to test a broad range of conditions unpredictable a priori. Moreover, SEAMLESS can be used as a design support tool to understand the behavior of possibly safety-critical systems in a controlled (simulated) environment. SEAMLESS relies on an improved and extended core (MAXIM-GPRT) equipped with powerful analytical tools.

### SIMULATIONS
The setup of the simulation is composed of 6 steps:


#### Simulation Settings
- Define the number of agents participating in the simulation;

  **Note:** To generate the reports, the number of agents must be > 0 and at one activity (e.g., task execution, negotiation, registration) has to occur;

- Set the bounds for the channel delay;

    **Note:** The value is computed randomly between MIN and MAX. If no delay  is needed, set MIN = MAX = 0;     

- Set the duration of the simulation;

- Set the scheduler of the Directory Facilitator (DF)
  **Note:** By selecting the Earliest Deadline First (EDF) scheduler, it is possible to enable the message handling via "servers" (e.g., Constant Bandwidth Server - CBS, Total Bandwidth Server - TBS, Dynamic Sporadic Server - DSS);

- If the negotiation is needed, toggle the option and choose the negotiation protocol among Contract Net (CNET), Contract Net with confirmation (CNCP), Englis Auction (EN), Dutch Auction (DU), Reservation Based Negotiation Protocol (RBN), and RBN with performance degradation RBN_PLUS.

**Note:** RBN and RBN_PLUS are only allowed to operate in real-time scenarios;

If the scheduler has to be the same for all the agents, toggle the option
*"Apply for every agent"*. It will enable the possibility of choosing a given scheduling algorithm to be set for all the agents participating in the simulation.


#### Configure Agents' scheduler
- If the *"Apply for every agent"* option has been selected, this step is not necessary. Thus, click on *"Skip"*;
- If the agents' scheduler has to be set singularly, it can be done by selecting it in the *"Scheduling Algorithm"* menu. Moreover, EDF has been selected, by selecting the toggle "Message server mode" enable the handling (reading/writing) of the messages among the agents via a server choosable from the menu *"Message server type"*.


#### Configure Servers
- If no scheduling algorithm allowing servers has been selected, click on *"Skip"*;
- If EDF has been selected as agent scheduler (in steps 1 or 2) and there is the need for servers handling aperiodic and sporadic tasks, select to which agent the server should be associated (Agent Id), define a Server Id, and its Budget and Period.

#### Knowledge and task sets configuration
- Select the id of the task;

  **Note:** the same Id can be assigned to similar or different tasks executed by different agents. Do not assign the same id to two tasks within the same agent. It will work, but nobody can say how... that will be on you.

- Set the identifier of the agent demanding and executing the task;

  **Note:** to assign the task to a given agent, executor and demander have to be the same. It has been left open the possibility to set them independently to impose/simulate pre-set negotiation to generate, and therefore study very specific scenarios;

- Define the computational time of the task, its period, relative deadline, and release time;

- If the task is a periodic task, leave *"-1"* in the proper field. Otherwise, set its number of occurrences;

- Generally, for the task added, first activation and last activation should be set at *"-1"*;
  **Note:** It has been left the possibility of modifying such values for generating and analyzing extremely specific case study;

 - If the task is not periodic, associate it to a server (setup at step 3). Otherwise, leave the value set to *"none"*;

 - To add the task to the task set toggle *"Add to the task set"*;
 
 - If such a task is public (available to be demanded by other agents) toggle *"Public"* and it will be inserted on the list of tasks a given agant might execute on demand;

- Repeat the procedure by clicking on the *"Add"* button to generate and configure other tasks needed for the simulation.

#### Configure Needs to be negotiated
- If no negotiation has been set or no negotiation is required, click on *"Skip"*;
- To set the needs, select the Agent Id the need refers to, the release time (point in time to release the need for a given task), the duration of the bidding window, when the negotiated task(s) should start to execute and (if needed) when they should stop, the required number of task execution (*-1* if periodic) and finally a minimum and maximum Task period (used by workload-based negotiation heuristics);

- Add more needs clicking on *"Add"*.

#### Summary before submitting the simulation
Before submitting the simulation, it is possible to:

- review the parameters added in the previous steps;
- see the summary of the configuration setup in the previous steps;
- submit the configuration and run the simulation.

If one or more errors in the configuration have occurred (thus generating an inconsistent setup), a list of features to be fixed is shown in a pop-up.

By clicking on *"review"*, it is possible to fix them (indicated in red to facilitate the process).

If the simulation ends successfully, a pop-up will confirm it, giving the possibility to visualize the results immediately or to close the dialog window and proceed.