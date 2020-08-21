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

import React from 'react'
import MDWrapper from '../../components/MDWrapper';
import maxim from '../../assets/maxim.md';


const sections = [
  { name: 'Features', href: 'features', level: 1 },
  // { name: 'Installation', href: 'installation', level: 1 },
  // { name: 'Developer\'s guide', href: 'developers-guide', level: 1 },
  // { name: 'Settings', href: 'settings', level: 2 },
  // { name: 'Agent Module', href: 'agent-module', level: 3 },
  // { name: 'Network Settings', href: 'network-settings', level: 3 },
  // { name: 'Simulation Settings', href: 'simulation-settings', level: 3 },
  { name: 'Core', href: 'core', level: 2 },
  { name: 'Agent', href: 'agent', level: 3 },
  { name: 'Initialization and Finalization', href: 'initialization-and-finalization', level: 4 },
  { name: 'Message Handling', href: 'message-handling', level: 4 },
  { name: 'Behaviors', href: 'behaviors', level: 4 },
  { name: 'Scheduler', href: 'scheduler', level: 3 },
  { name: 'Task', href: 'task', level: 3 },
  { name: 'Message Task', href: 'message-task', level: 3 },
  { name: 'Server', href: 'server', level: 3 },
  { name: 'Service', href: 'service', level: 3 },
  { name: 'Need', href: 'need', level: 3 },
  { name: 'Bid', href: 'bid', level: 3 },
  { name: 'Negotiation Session', href: 'negotiation-session', level: 3 },
  { name: 'Agent Message', href: 'agentmsg', level: 3 },
  { name: 'Handlers', href: 'handlers', level: 3 },
  { name: 'Utilities', href: 'utilities', level: 2 },
]

export default function About() {
  return (
    <MDWrapper title='MAXIM-GPRT' file={maxim} sections={sections} />
  )
}