import React, { useEffect, useState } from 'react';
import Typography from '../../components/Typography';
import {
  Box,
  Grid,
  Hidden
} from '@material-ui/core';
import ContentNav from '../../components/ContentNav';
import Markdown from '../../components/Markdown';
import maxim from '../../assets/maxim.md';
import ScrollTop from '../../components/ScrollTop';
import Fab from '@material-ui/core/Fab';
import KeyboardArrowUpIcon from '@material-ui/icons/KeyboardArrowUp';

const sections = [
  { name: 'Features', href: 'features', level: 1 },
  { name: 'Installation', href: 'installation', level: 1 },
  { name: 'Developer\'s guide', href: 'developers-guide', level: 1 },
  { name: 'Settings', href: 'settings', level: 2 },
  { name: 'Agent Module', href: 'agent-module', level: 3 },
  { name: 'Network Settings', href: 'network-settings', level: 3 },
  { name: 'Simulation Settings', href: 'simulation-settings', level: 3 },
  { name: 'Core', href: 'core', level: 2 },
  { name: 'Agent', href: 'agent', level: 3 },
  { name: 'Initialization and Finalization', href: 'initialization-and-finalization', level: 3 },
  { name: 'Message Handling', href: 'message-handling', level: 3 },
  { name: 'Behaviors', href: 'behaviors', level: 3 },
  { name: 'Scheduler', href: 'scheduler', level: 3 },
  { name: 'Task', href: 'task', level: 3 },
  { name: 'Message Task', href: 'msgtask', level: 3 },
  { name: 'Server', href: 'server', level: 3 },
  { name: 'Service', href: 'service', level: 3 },
  { name: 'Need', href: 'need', level: 3 },
  { name: 'Bid', href: 'bid', level: 3 },
  { name: 'Negotiation Session', href: 'negsession', level: 3 },
  { name: 'Agent Message', href: 'agentmsg', level: 3 },
  { name: 'Handlers', href: 'handlers', level: 3 },
  { name: 'Utilities', href: 'utilities', level: 2 },
]

function About(props) {
  const [markdown, setMarkdown] = useState('');

  const fetchMd = async name => {
    const res = await fetch(maxim);
    const text = await res.text();
    setMarkdown(text);
  }

  useEffect(() => {
    // Load the md file on mounting
    fetchMd(maxim);
  }, []);

  return (
    <>
      <Grid container spacing={3}>
        <Grid item xs={12} sm={10}>
          <Box mr={3}>
            <Box pb={2} pt={4} id="back-to-top-anchor">
              <Typography variant='h2' className={props.classes.title}>
                Maxim-GPRT
              </Typography>
            </Box>
            <Markdown children={markdown} />
          </Box>
        </Grid>
        <Grid item sm={2}>
          <Hidden smDown>
            <Box pl={2}>
              <ContentNav sections={sections} />
            </Box>
          </Hidden>
        </Grid>
      </Grid>
      <Hidden smUp>
        <ScrollTop selector='#back-to-top-anchor' {...props}>
          <Fab color="secondary" size="small" aria-label="scroll back to top">
            <KeyboardArrowUpIcon />
          </Fab>
        </ScrollTop>
      </Hidden>
    </>
  )
}

export default About;