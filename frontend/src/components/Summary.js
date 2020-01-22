import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import ExpansionPanel from '@material-ui/core/ExpansionPanel';
import ExpansionPanelSummary from '@material-ui/core/ExpansionPanelSummary';
import ExpansionPanelDetails from '@material-ui/core/ExpansionPanelDetails';
import Typography from '@material-ui/core/Typography';
import ExpandMoreIcon from '@material-ui/icons/ExpandMore';
import KnowledgeTable from './tables/KnowledgeTable';
import NeedsTable from './tables/NeedsTable';
import ServersTable from './tables/ServersTable';
import Grid from '@material-ui/core/Grid';
import Box from '@material-ui/core/Box';
import * as constants from '../utils/constants'

const useStyles = makeStyles(theme => ({
  root: {
    width: '100%',
  },
  heading: {
    fontSize: theme.typography.pxToRem(15),
    fontWeight: theme.typography.fontWeightBold,
  },
  '@global': {
    '.MuiExpansionPanelDetails-root': {
      padding: '5px 24px'
    },
    '.MuiExpansionPanelSummary-root': {
      display: 'grid',
      gridAutoFlow: 'column',
      alignItems: 'center',
      justifyContent: 'start',
      overflowY: 'hidden'
    }
  },
  list: {
    listStyleType: 'none',
    '& span': {
      fontWeight: theme.typography.fontWeightBold,
    }
  },
  list_title: {
    paddingBottom: theme.spacing(2),
    ...theme.typography.h5,
    color: theme.palette.grey[600]
  }
}));

export default function Summary(props) {
  const { knowledge, needs, servers, agents, ids, config } = props;
  const classes = useStyles();

  const getStructureById = (structure, id, field) => {
    let res = [];
    Object.keys(structure).forEach(key => {
      let entry = structure[key];
      if (entry[field] === id || entry[field] === -1) {
        res.push(entry);
      }
    })
    return res;
  }

  return (
    <div className={classes.root}>
      <Grid container spacing={3}>
        <Grid item xs>
          <Box pb={2}>
            <Typography className={classes.list_title} component='p'>Simulator options</Typography>
            <Typography className={classes.list} component='li'><span>Date: </span>
              {props.date ? new Date(props.date).toLocaleString() : new Date(config.date).toLocaleString()}</Typography>
            <Typography className={classes.list} component='li'><span>Name: </span> {config.sim_name}</Typography>
            <Typography className={classes.list} component='li'><span>Minimum channel delay:</span> {config.min_delay}</Typography>
            <Typography className={classes.list} component='li'><span>Maximum channel delay:</span> {config.max_delay}</Typography>
            <Typography className={classes.list} component='li'><span>Simulation time:</span> {config.time}</Typography>
          </Box>
        </Grid>
        <Grid item xs>
          <Box pb={2}>
            <Typography className={classes.list_title} component='p'>Agents options</Typography>
            <Typography className={classes.list} component='li'><span>Number of Agents:</span> {config.agents_n}</Typography>
            <Typography className={classes.list} component='li'><span>DF Scheduling Algorithm:</span> {constants.SchedType[config.DF_sched_type]}</Typography>
            {config.DF_sched_type === 1 && <Typography className={classes.list} component='li'><span>Quantum:</span> {config.DF_quantum}</Typography>}
            <Typography className={classes.list} component='li'><span>DF Message server mode:</span> {String(config.DF_msg_server_mode ? '✓' : '✗')}</Typography>
            {config.DF_msg_server_mode &&
              <>
                <Typography className={classes.list} component='li'><span>DF Message server type:</span> {constants.ServerType[config.DF_server_type]}</Typography>
                <Typography className={classes.list} component='li'><span>DF Message server budget:</span> {config.DF_server_budget}</Typography>
                <Typography className={classes.list} component='li'><span>DF Message server period:</span> {config.DF_server_period}</Typography>
              </>
            }
            <Typography className={classes.list} component='li'><span>Apply for every agent:</span> {config.apply_for_all ? '✓' : '✗'}</Typography>
            {config.apply_for_all &&
              <>
                <Typography className={classes.list} component='li'><span>Scheduling Algorithm:</span> {constants.SchedType[config.sched_type]}</Typography>
                {config.sched_type === 1 && <Typography className={classes.list} component='li'><span>Quantum:</span> {config.quantum}</Typography>}
                <Typography className={classes.list} component='li'><span>Message server mode:</span> {config.msg_server_mode ? '✓' : '✗'}</Typography>
                {config.msg_server_mode &&
                  <>
                    <Typography className={classes.list} component='li'><span>Message server type:</span> {constants.ServerType[config.server_type]}</Typography>
                    <Typography className={classes.list} component='li'><span>Message server budget:</span> {config.server_budget}</Typography>
                    <Typography className={classes.list} component='li'><span>Message server period:</span> {config.server_period}</Typography>
                  </>
                }
              </>
            }
          </Box>
        </Grid>
        <Grid item xs>
          <Box pb={2}>
            <Typography className={classes.list_title} component='p'>Negotiation options</Typography>
            <Typography className={classes.list} component='li'><span>Use negotiation:</span> {config.use_neg ? '✓' : '✗'}</Typography>
            {config.use_neg &&
              <>
                <Typography className={classes.list} component='li'><span>Negotiation Protocol:</span> {constants.NegType[config.neg_type]}</Typography>
                <Typography className={classes.list} component='li'><span>Contractor Heuristic:</span> {constants.ContractorPolicies[config.contr_h]}</Typography>
                <Typography className={classes.list} component='li'><span>Bidder Heuristic:</span> {constants.BidderPolicies[config.bidder_h]}</Typography>
              </>
            }
          </Box>
        </Grid>
      </Grid>
      {ids.map(id => {
        return (
          <ExpansionPanel key={id}>
            <ExpansionPanelSummary
              expandIcon={<ExpandMoreIcon />}
              aria-controls="agent-panel"
              id="agent-panel-header"
            >
              <Typography component='span' className={classes.heading}>Agent {id}</Typography>
            </ExpansionPanelSummary>
            <ExpansionPanelDetails>
              <Box pt={1} pb={2}>
                {/* <Typography className={classes.list_title} component='p'>Settings</Typography> */}
                {config.apply_for_all
                  ? <>
                    <Typography className={classes.list} component='li'>
                      <span>Scheduling Algorithm: </span>
                      {constants.SchedType[config.sched_type]}
                    </Typography>
                    {config.sched_type === constants.SchedTypeEnum['RR']
                      && <>
                        <Typography className={classes.list} component='li'>
                          <span>Quantum: </span>
                          {config.quantum}
                        </Typography>
                      </>
                    }
                    <Typography className={classes.list} component='li'>
                      <span>Message server mode: </span>
                      {config.msg_server_mode ? '✓' : '✗'}
                    </Typography>
                    {config.msg_server_mode &&
                      <>
                        <Typography className={classes.list} component='li'>
                          <span>Message server type: </span>
                          {constants.ServerType[config.server_type]}
                        </Typography>
                        <Typography className={classes.list} component='li'>
                          <span>Message server budget: </span>
                          {config.server_budget}
                        </Typography>
                        <Typography className={classes.list} component='li'>
                          <span>Message server period: </span>
                          {config.server_period}
                        </Typography>
                      </>
                    }
                  </>
                  : <>
                    <Typography className={classes.list} component='li'>
                      <span>Scheduling Algorithm: </span>
                      {constants.SchedType[agents[id].sched_type]}
                    </Typography>
                    {agents[id].sched_type === 1
                      && <>
                        <Typography className={classes.list} component='li'>
                          <span>Quantum: </span>
                          {agents[id].quantum}
                        </Typography>
                      </>
                    }
                    <Typography className={classes.list} component='li'>
                      <span>Message server mode: </span>
                      {agents[id].msg_server_mode ? '✓' : '✗'}
                    </Typography>
                    {agents[id].msg_server_mode &&
                      <>
                        <Typography className={classes.list} component='li'>
                          <span>Message server type: </span>
                          {constants.ServerType[agents[id].server_type]}
                        </Typography>
                        <Typography className={classes.list} component='li'>
                          <span>Message server budget: </span>
                          {agents[id].server_budget}
                        </Typography>
                        <Typography className={classes.list} component='li'>
                          <span>Message server period: </span>
                          {agents[id].server_period}
                        </Typography>
                      </>
                    }
                  </>
                }
              </Box>
            </ExpansionPanelDetails>
            <ExpansionPanelDetails>
              <ExpansionPanel elevation={0} style={{ overflowX: 'auto' }}>
                <ExpansionPanelSummary
                  expandIcon={<ExpandMoreIcon />}
                  aria-controls="knowledge-panel"
                  id="knowledge-panel-header"
                >
                  <Typography component='span' className={classes.heading}>Knowledge</Typography>
                </ExpansionPanelSummary>
                <ExpansionPanelDetails>
                  <KnowledgeTable knowledge={getStructureById(knowledge, id, 'agentExecutor')} />
                </ExpansionPanelDetails>
              </ExpansionPanel>
            </ExpansionPanelDetails>
            <ExpansionPanelDetails>
              <ExpansionPanel elevation={0} style={{ overflowX: 'auto' }}>
                <ExpansionPanelSummary
                  expandIcon={<ExpandMoreIcon />}
                  aria-controls="servers-panel"
                  id="servers-panel-header"
                >
                  <Typography component='span' className={classes.heading}>Servers</Typography>
                </ExpansionPanelSummary>
                <ExpansionPanelDetails>
                  <ServersTable servers={getStructureById(servers, id, 'agent_id')} />
                </ExpansionPanelDetails>
              </ExpansionPanel>
            </ExpansionPanelDetails>
            <ExpansionPanelDetails>
              <ExpansionPanel elevation={0} style={{ overflowX: 'auto' }}>
                <ExpansionPanelSummary
                  expandIcon={<ExpandMoreIcon />}
                  aria-controls="needs-panel"
                  id="needs-panel-header"
                >
                  <Typography component='span' className={classes.heading}>Needs</Typography>
                </ExpansionPanelSummary>
                <ExpansionPanelDetails>
                  <NeedsTable needs={getStructureById(needs, id, 'agent_id')} />
                </ExpansionPanelDetails>
              </ExpansionPanel>
            </ExpansionPanelDetails>
          </ExpansionPanel>
        )
      })
      }
    </div>
  );
}
