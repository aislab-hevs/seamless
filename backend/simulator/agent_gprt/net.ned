//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 


//
// TODO documentation
//

simple agent
{	
    @display("i=block/user"); 
    int sched_type @prompt("Scheduler type\n0: FCFS\n1: RR\n2: EDF\n3: SJF\n4: RM");	//scheduler type to use (0 = FCFS, 1 = RR, 2 = EDF, 3 = SJF, 4 = RM)
    int server_type @prompt("Message server type\n0: CBS\n1: TBS\n2: DSS");				//server type to use for messages (0 = CBS, 1 = TBS, 2 = DSS)
    int neg_type @prompt("Negotiation type\n0: CNET\n1: RBN\n2: CNCP\n3: EN\n4: DU\n5: RBN_PLUS");			//negotiation type to use (0 = CNET, 1 = RBN, 2 = CNCP, 3 = EN, 4 = DU, 5 = RBN_PLUS)
    int bidder_heuristic;											    //heuristic type to use (0 = FIRST, 1 = RANDOM, 2 = RAND_SUBSET, 3 = BEST)
    int contractor_heuristic;
    bool msg_server_mode;
    double neg_timeout = default(0);
    double quantum = default(3);
    double server_budget;
    double server_period;
//    volatile double delayTime @unit(s);   // delay before sending back message

    //statistic-related
    //deadline miss count
    //@signal[ddl_miss](type="long");
    //@statistic[ddl_miss_count](title="deadline miss"; source="ddl_miss"; record=vector,stats; interpolationmode=none);

    gates:
        inout gate[];
        //input dirGate @directIn;  		//not used (yet?)

}

//
// TODO documentation
//
network net_0
{
    parameters:
        //int aAddress;						//not used (yet?)
        int n @prompt("Number of clients") = default(1);
        int k = 0;
        string timestamp;
        string user = default("peppe");
        @display("bgb=331,135");

//        @display("bgb=611,287");

    types:
        channel Channel extends ned.DelayChannel
        {
//            delay = 100ms;
        }
    submodules:
        DF: agent {
            //  @display("p=41,40");
            @display("i=,gold;p=164.01999,66.72");
        }
        ag[n]: agent;
    connections:

        for i=0..n-1 {
            ag[i].gate++ <--> Channel <--> DF.gate++;
        }

        for i=0..n-2, for k=i+1..n-1 {
            ag[i].gate++ <--> Channel <--> ag[k].gate++;
        }
}

