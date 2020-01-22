import React from 'react'
import MDWrapper from '../../components/MDWrapper';
import research from '../../assets/research.md';

const sections = [
  { name: 'Summary', href: 'Summary', level: 1 },
  { name: 'Simulations', href: 'Simulations', level: 1 },
  { name: 'Tasksets', href: 'Tasksets', level: 1 },
  { name: 'Needs', href: 'Needs', level: 1 }
]

export default function Howto() {
  return (
    <MDWrapper title='Research' file={research} />
  )
}