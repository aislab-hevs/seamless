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