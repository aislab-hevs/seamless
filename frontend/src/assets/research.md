Modern society is increasingly connected with electronic and mobile devices, reconciling the virtual and real world in Cyber-Physical Systems (CPS). Such systems continuously interact (through sensors, actuators, and message exchange) with their surroundings (environment and other entities). The collected information can be locally or remotely elaborated, depending on the intelligence and capabilities of the entities. In CPS, the correctness of the results does not solely depend on the correctness of the delivered value, it also depends on the time in which such a result is delivered [5]. For example, a delayed actuation of the brakes of a car (i.e., when a collision has already occurred) makes the result of the action useless and potentially dangerous.

In the last decades, the research in intelligent agents led to the development of many approaches in topics such as distributed problem solving and optimization applied to various domains (e.g., eHealth [8], assistive technologies [7], manufacturing [25], and energy trading [25]). Research in distributed autonomous agent systems, so-called Multi-Agent Systems (MAS), focused on the achievement of optimal solutions, e.g., in terms of resource usage, performance, communication, agreement, etc. However, unfortunately, these studies have foregone the crucial element of "time", which is essential in safety-critical applications. Hence, current MAS usually cannot provide timing guarantees: they are not real-time compliant [24]. 

It is worth recalling that agents and MAS are characterized by four pillars operating simultaneously, namely *(i)* behavioral models (e.g., the intelligent and strategic set of actions that allows both single agents and the whole community to pursue their goals), *(ii)* a communication middleware (e.g., to allow the interactions among the agents), *(iii)* local policies (e.g., task schedulers and heuristics for decision making), and *(iv)* the negotiation protocol (e.g., the policy to achieve an agreement on a task execution). Timing compliance can be achieved only if all these elements are simultaneously time-aware [28]. However, the unpredictability that results from this lack of compliance is still hampering MAS adoption in CPS, especially for safety-critical scenarios [25]. Due to the high dynamicity of MAS, to study and predict their behaviors a priori is prohibitive and not yet possible. Therefore, there is a clear need for a tool supporting the in-depth analysis of the MAS’s core elements behavior in relation to time reliability. The development of this tool is the goal of this proposal.

Further studies employed the simulator relized in the SEAMLESS project to study the design and simulation of a MAS distributed over wearable sensors interacting via real-time processed streams of data for rehabilitation purposes [30]
Finally, SEAMLESS is currently used in the teaching of master courses dedicated to MAS and real-time systems at the *Università Politecnica delle Marche*, and *Sant'Anna School of Advanced Studies*.

#### SEAMLESS Source Code
https://github.com/aislab-hevs/seamless

#### References

[1] Calvaresi, D., Albanese, G., Marinoni, M., Dubosson, F., Sernani, P., Dragoni, A. F., & Schumacher, M. 
*Timing Reliability for Local Schedulers in Multi-Agent Systems.*
In Proceedings of 1ST International Workshop on Real-Time Compliant Multi-Agent Systems.

[2] Calvaresi, D., Albanese, G., Dubosson, F., Marinoni, M., & Schumacher, M. 
*A Task-sets Generator for Supporting the Analysis of Multi-Agent Systems under General Purpose and Real-Time Conditions*.
In Proceedings of 1ST International Workshop on Real-Time Compliant Multi-Agent Systems.

[3] Bordini, R.H., Hübner, J.F.: Bdi agent programming in agentspeak using jason. In: Proceedings of the 6th international conference on Computational Logic in Multi-Agent Systems (2005).

[4] Bousquet, F., Bakam, ., Proton, H., Le Page, C.: Cormas: common-pool resources and multi-agent systems. In: International Conference on Industrial, Engineering and Other Applications of Applied Intelligent Systems. pp. 826–837. Springer (1998)

[5] Buttazzo, G.: Hard real-time computing systems: predictable scheduling algorithms and applications, vol. 24. Springer Science & Business Media (2011)

[7] Calvaresi, D., Cesarini, D., Sernani, P., Marinoni, M., Dragoni, A., Sturm, A.: Exploring the ambient assisted living domain: a systematic review. Journal of Ambient Intelligence and Humanized Computing pp. 1–19 (2016)

[8] Calvaresi, D., Claudi, A., Dragoni, A., Yu, E., Accattoli, D., Sernani, P.: A goal-oriented requirements engineering approach for the ambient assisted living domain. In: Proceedings of the 7th International Conference on PErvasive Technologies Related to Assistive Environments. pp. 20:1–20:4. PETRA ’14 (2014), http://doi.acm.org/10.1145/2674396.2674416

[9] Calvaresi, D., Marinoni, M., Lustrissimini, L., Appoggetti, K., Sernani, P., Dragoni, A.F.,
Schumacher, M., Buttazzo, G.: Local scheduling in multi-agent systems: getting ready for safety-critical scenarios. In: Proceedings of 15th European Conference on Multi-Agent Systems (2017)

[10] Calvaresi, D., Schumacher, M., Marinoni, M., Hilfiker, R., Dragoni, A., Buttazzo, G.: Agent-based systems for telerehabilitation: strengths, limitations and future challenges. In: proceedings of X Workshop on Agents Applied in Health Care (2017)

[12] Collier, N.: Repast: An extensible framework for agent simulation. The University of Chicagos Social Science Research 36, 2003 (2003)

[13] Grignard, A., Taillandier, P., Gaudou, B., Vo, D.A., Huynh, N.Q., Drogoul, A.: Gama 1.6:
Advancing the art of complex agent-based modeling and simulation. In: International Conference on Principles and Practice of Multi-Agent Systems. pp. 117–131. Springer (2013)

[14] Gutknecht, O., Ferber, J.: The madkit agent platform architecture. In: Workshop on Infrastructure for Scalable Multi-Agent Systems at the International Conference on Autonomous Agents. pp. 48–55. Springer (2000)

[16] Hsieh, F.: Modeling and control of holonic manufacturing systems based on extended con-
tract net protocol. In: Proceedings of the American Control Conference. vol. 6, pp. 5037–5042 (2002)

[18] Luke, S., Cioffi-Revilla, C., Panait, L., Sullivan, K.: Mason: A new multi-agent simulation
toolkit. In: Proceedings of the 2004 swarmfest workshop. pp. 316–327 (2004)

[19] McArthur, S.D.J., Davidson, E.M., Catterson, V.M., Dimeas, A.L., Hatziargyriou, N.D.,
Ponci, F., Funabashi, T.: Multi-agent systems for power engineering applications 2014;parti: Concepts, approaches, and technical challenges. IEEE Transactions on Power Systems pp.1743–1752 (2007)

[20] Minar, N., Burkhart, R., Langton, C., Askenazi, M., et al.: The swarm simulation system: A toolkit for building multi-agent simulations (1996)

[21] TILab: JADE Manual. http://jade.tilab.com/doc/programmersguide.pdf, [Accessed Sept’18]

[22] Tisue, S., Wilensky, U.: Netlogo: Design and implementation of a multi-agent modeling environment. In: Proceedings of agent. vol. 2004, pp. 7–9 (2004)

[23] Julian, Vicente, and Vicent Botti. "Developing real-time multi-agent systems." Integrated Computer-Aided Engineering 11.2 (2004): 135-149.

[24] Calvaresi, Davide, et al. "The challenge of real-time multi-agent systems for enabling IoT and CPS." Proceedings of the International Conference on Web Intelligence. ACM, 2017.

[25] Davide Calvaresi, Aldo Franco Dragoni, and Giorgio C. Buttazzo, editors.Proceedings of the 1st International Workshop on Real-Time compliant Multi-Agent Systems (RTcMAS) co-located with the Federated Artificial Intelligence Meeting, Stockholm, Sweden, July 15th, 2018, volume 2156 of CEUR Workshop Proceedings. CEUR-WS.org, 2018.

[26] Calvaresi, D., Appoggetti, K., Lustrissimi, L., Marinoni, M., Sernani, P., Dragoni, A. F., & Schumacher, M. (2018). Multi-Agent Systems' Negotiation Protocols for Cyber-Physical Systems: Results from a Systematic Literature Review. In ICAART (1) (pp. 224-235).

[27] Wooldridge, M. J. (1992). The logical modelling of computational multi-agent systems (Doctoral dissertation, University of Manchester, Institute of Science and Technology).

[28] Calvaresi, D., Marinoni, M., Lustrissimini, L., Appoggetti, K., Sernani, P., Dragoni, A. F., ... & Buttazzo, G. (2017). Local scheduling in multi-agent systems: getting ready for safety-critical scenarios. In Multi-Agent Systems and Agreement Technologies (pp. 96-111). Springer, Cham.

[29] Calvaresi, D., Albanese, G., Calbimonte, J. P., & Schumacher, M. (2020, October). SEAMLESS: Simulation and Analysis for Multi-Agent System in Time-Constrained Environments. In International Conference on Practical Applications of Agents and Multi-Agent Systems (pp. 392-397). Springer, Cham.

[30] Calvaresi, D., & Calbimonte, J. P. (2020). Real-time compliant stream processing agents for physical rehabilitation. Sensors, 20(3), 746.
