const ContractorPoliciesEnum = {
    [-1]: 'None',
    0: 'First',
    1: 'Random',
    2: 'Random Subset',
    8: 'All'
};

const BidderPoliciesEnum = {
    [-1]: 'None',
    0: 'First',
    3: 'Best',
    4: 'Workload Balance (Minimum Period)', // Minimum period - WorkLoad Balance (minimum utilization)
    5: 'Workload Maximization (Minimum Period)', // Minimum period - Workload Maximization (maximum utilization)
    6: 'Workload Balance',
    7: 'Workload Maximization',
};

const SchedTypeEnum = {
    0: 'First Come First Served',
    1: 'Round Robin',
    2: 'Earliest Deadline First',
    3: 'Shortest Job First',
    4: 'Rate Monotonic'
};

const NegTypeEnum = {
    [-1]: 'None',
    0: 'Contract Net',
    1: 'Reservation Based Negiotiation',
    2: 'Contract Net With Confirmation',
    3: 'English Auction',
    4: 'Dutch Auction',
    5: 'Reservation Based Negotiation With Degradation',
};

const ServerTypeEnum = {
    [-1]: 'None',
    0: 'Constant Bandwidth Server',
    1: 'Total Bandwidth Server',
    2: 'Dynamic Sporadic Server',
};

module.exports = {
    ContractorPoliciesEnum,
    BidderPoliciesEnum,
    SchedTypeEnum,
    NegTypeEnum,
    ServerTypeEnum
}