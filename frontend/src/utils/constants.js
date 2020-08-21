/*
 * Copyright (c) 2020, HES-SO Valais-Wallis (https://www.hevs.ch)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// const colors = ['#e7245b', '#000000', '#028482', '#9932CC', '#000080', '#CD950C', '#00CED1', '#8B4513', '#551A8B', '#8B0000'];
const colors = [
    '#e7245b',
    '#000000',
    '#008080',
    '#911eb4',
    '#000075',
    '#f58231',
    '#4363d8',
    '#f032e6',
    '#800000', 
    '#3cb44b',
    '#9a6324', 
    '#053f5e',
    '#834c69', 
    '#ed6363',
    '#310a5d', 
    '#17b794',
    '#808000', 
    '#69779b',
    '#44000d',
    '#3c6562',
];

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