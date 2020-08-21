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