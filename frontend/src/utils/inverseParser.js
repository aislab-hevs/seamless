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

const inverseParse = structure => {
    let inverse = {};
    let index = 0;
    for (let agent in structure) {
        structure[agent].forEach((el) => {
            inverse[index] = el;
            index++
        });
    }
    return inverse;
}

const inverseParseConfig = config => {
    let inverse = {};
    let delay = config[`**.delay`];
    inverse.apply_for_all = config[`# apply_for_all`] === 'true' ? true : false;
    inverse.sim_name = config[`# Name`];
    inverse.use_neg = config[`*.DF.neg_type`] !== "-1";
    inverse.DF_msg_server_mode = config[`DF.msg_server_mode`];
    inverse.msg_server_mode =  config.hasOwnProperty(`*.ag[*].msg_server_mode`) ? config[`*.ag[*].msg_server_mode`] === 'true' : false;
    inverse.agents_n = config[`*.n`];
    inverse.min_delay = delay.substring(delay.indexOf('(') + 1, delay.lastIndexOf('ms,'));
    inverse.max_delay = delay.substring(delay.indexOf(', ') + 2, delay.lastIndexOf('ms)'));
    inverse.time = config[`sim-time-limit`].split('s')[0];
    inverse.DF_sched_type = Number(config[`*.DF.sched_type`]);
    inverse.DF_server_type = Number(config[`*.DF.server_type`]);
    inverse.DF_server_budget = config.hasOwnProperty(`*.DF.server_budget`) ? Number(config[`*.DF.server_budget`]) : -1;
    inverse.DF_server_period = config.hasOwnProperty(`*.DF.server_period`) ? Number(config[`*.DF.server_period`]) : -1;
    inverse.sched_type = config.hasOwnProperty(`*.ag[*].sched_type`) ? Number(config[`*.ag[*].sched_type`]) : -1;
    inverse.DF_quantum = config.hasOwnProperty(`*.DF.quantum`) ? config[`*.ag[*].quantum`] : -1;
    inverse.quantum = config.hasOwnProperty(`*.ag[*].quantum`) ? config[`*.ag[*].quantum`] : -1;
    inverse.server_type = config.hasOwnProperty(`*.ag[*].server_type`) ? Number(config[`*.ag[*].server_type`]) : -1;
    inverse.server_budget = config.hasOwnProperty(`*.ag[*].server_budget`) ? Number(config[`*.ag[*].server_budget`]) : -1;
    inverse.server_period = config.hasOwnProperty(`*.ag[*].server_period`) ? Number(config[`*.ag[*].server_period`]) : -1;
    inverse.neg_type = Number(config[`*.DF.neg_type`]);
    inverse.contr_h = Number(config[`*.DF.contractor_heuristic`]);
    inverse.bidder_h = Number(config[`*.DF.bidder_heuristic`]);
    // console.log(inverse);
    // console.log(config);
    return inverse;
}

export {
    inverseParse,
    inverseParseConfig
}