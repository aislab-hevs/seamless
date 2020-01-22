import React from 'react'
import AgentForm from './AgentForm';
import TaskForm from './TaskForm';
import ServerForm from './ServerForm';
import NeedForm from './NeedForm';
import HistoryButtons from './HistoryButtons';
import { makeStyles } from '@material-ui/core/styles';
import {
  Grid,
  MenuItem
} from '@material-ui/core'

const useStyles = makeStyles(theme => ({
  root: {
    width: '90%',
  },
}))

export default function ComboForm(props) {
  const { isDisabled, agents_n, structureIndex, setStructureIndex, structure, setStructure, header, activeStep, error, setError } = props;
  const classes = useStyles();

  const getAgentsMenuItems = () => {
    let options = [];
    for (let i = 0; i < agents_n; i++) {
      options.push(<MenuItem
        key={i}
        value={`${i}`}>{i}
      </MenuItem>)
    }
    return options;
  }

  const getActiveForm = () => ({
    '1': <AgentForm
      isDisabled={isDisabled}
      agents_n={agents_n}
      agentIndex={structureIndex}
      agents={structure}
      setAgents={setStructure}
      error={error}
    />,
    '2': <ServerForm
      rt_agents={props.rt_agents}
      agents_n={agents_n}
      serverIndex={structureIndex}
      servers={structure}
      setServers={setStructure}
      error={error}
    />,
    '3': <TaskForm
      getAgentsMenuItems={getAgentsMenuItems}
      taskIndex={structureIndex}
      knowledge={structure}
      setKnowledge={setStructure}
      servers={props.servers}
      error={error}
    />,
    '4': <NeedForm
      getAgentsMenuItems={getAgentsMenuItems}
      needIndex={structureIndex}
      needs={structure}
      setNeeds={setStructure}
      tasks={props.tasks}
      neg_type={props.neg_type}
      use_neg={props.use_neg}
      error={error}
    />
  });

  return (
    <>
      <Grid container className={classes.root} spacing={1}>
        <Grid item xs={12} md={9}>
          {getActiveForm()[activeStep]}
        </Grid>
        <Grid item xs={12} md={3}>
          <HistoryButtons
            activeStep={activeStep}
            header={header}
            structure={structure}
            setStructure={setStructure}
            structureIndex={structureIndex}
            setStructureIndex={setStructureIndex}
            error={error}
            setError={setError}
          />
        </Grid>
      </Grid>
    </>
  )
}