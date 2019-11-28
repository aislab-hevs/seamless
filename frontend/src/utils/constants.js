const colors = ['#e7245b', '#000000', '#028482', '#9932CC', '#000080', '#CD950C', '#00CED1', '#8B4513', '#551A8B', '#8B0000'];

const ContractorPoliciesEnum = {
    'FIRST': 0,
    'RANDOM': 1,
    'RAND_SUBSET': 2,
    'ALL': 8
};

const BidderPoliciesEnum = {
    'FIRST': 0,
    'BEST': 3,
    'MIN_WLB': 4, // Minimum period - WorkLoad Balance (minimum utilization)
    'MIN_WLM': 5, // Minimum period - Workload Maximization (maximum utilization)
    'WLB': 6,
    'WLM': 7,
};

const SchedTypeEnum = {
    'FCFS': 0,
    'RR': 1,
    'EDF': 2,
    'SJF': 3,
    'RM': 4
};

const NegTypeEnum = {
    'CNET': 0,
    'RBN': 1,
    'CNCP': 2,
    'EN': 3,
    'DU': 4,
    'RBN_PLUS': 5,
};

const ServerTypeEnum = {
    'CBS': 0,
    'TBS': 1,
    'DSS': 2
};

// reverse mapping
const ContractorPolicies = {
    0: 'FIRST',
    1: 'RANDOM',
    2: 'RAND_SUBSET',
    8: 'ALL'
};

const BidderPolicies = {
    0: 'FIRST',
    3: 'BEST',
    4: 'MIN_WLB', // Minimum period - WorkLoad Balance (minimum utilization)
    5: 'MIN_WLM', // Minimum period - Workload Maximization (maximum utilization)
    6: 'WLB',
    7: 'WLM',
};

const SchedType = {
    0: 'FCFS',
    1: 'RR',
    2: 'EDF',
    3: 'SJF',
    4: 'RM'
};

const NegType = {
    0: 'CNET',
    1: 'RBN',
    2: 'CNCP',
    3: 'EN',
    4: 'DU',
    5: 'RBN_PLUS',
};

const ServerType = {
    0: 'CBS',
    1: 'TBS',
    2: 'DSS'
};

export {
    colors,
    ContractorPoliciesEnum,
    BidderPoliciesEnum,
    SchedTypeEnum,
    NegTypeEnum,
    ServerTypeEnum,
    ContractorPolicies,
    BidderPolicies,
    SchedType,
    NegType,
    ServerType
}