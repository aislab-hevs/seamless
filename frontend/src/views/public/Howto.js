import React from 'react'
import MDWrapper from '../../components/MDWrapper';
import howto from '../../assets/howto.md';

const sections = [
  { name: 'Introduction', href: 'introduction', level: 1 },
  { name: 'Simulation Settings', href: 'simulation-settings', level: 1 },
  { name: 'Agents', href: 'configure-agents-scheduler', level: 1 },
  { name: 'Servers', href: 'configure-servers', level: 1 },
  { name: 'Tasks', href: 'knowledge-and-task-sets-configuration', level: 1 },
  { name: 'Needs', href: 'configure-needs-to-be-negotiated', level: 1 },
  { name: 'Summary', href: 'summary-before-submitting-the-simulation', level: 1 }
]

export default function Howto() {
  return (
    <MDWrapper title='Guide' file={howto} sections={sections} />
  )
}