import React, { useEffect } from 'react';
import { makeStyles } from '@material-ui/core/styles';
import CustomSelect from './CustomSelect';
import {
  TextField,
  FormLabel,
  FormGroup,
  FormControlLabel,
  Switch,
  Grid
} from '@material-ui/core';
import * as constants from '../../utils/constants';

const useStyles = makeStyles(theme => ({
  spaced: {
    margin: theme.spacing(1),
    maxWidth: 240,
  }
}));


export default function AgentForm(props) {
  const { isDisabled, setAgents, agents, agentIndex, agents_n, error } = props;
  const classes = useStyles();

  // WARNING! Dark magic here
  const handleChange = (index, prop) => event => {
    event.persist();
    if (!agents[index]) agents[index] = {};
    setAgents(agents => ({
      ...agents, // keep old agents (whole)...
      [index]: {
        ...agents[index], // keep already set properties...
        [event.target.name]: event.target[prop] // update new values
      }
    }));
  };

  const initValue = (param, value) => {
    agents[agentIndex][param] = agents[agentIndex][param] !== undefined
      ? agents[agentIndex][param]
      : value;
  }

  useEffect(() => {
    const currAgents = Object.keys(agents).length;
    const ag_n = parseInt(agents_n);
    for (let i = 1; i < ag_n; i++) {
      if (!agents[i]) agents[i] = {};
    }
    if (currAgents > ag_n) {
      for (let i = ag_n; i < currAgents; i++) {
        delete agents[i];
      }
    }
    setAgents(agents => ({ ...agents }));
    initValue('msg_server_mode', false);
    initValue('quantum', 1);
    // initValue('server_type', -1); // moved in backend parser
  }, [agentIndex])

  return (
    <div className={classes.root}>
      <FormLabel component="legend">Agent Configuration</FormLabel>
      <Grid container spacing={4}>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            <TextField
              id="agent_id"
              name="agent_id"
              className={classes.spaced}
              label="Agent Id"
              margin="normal"
              fullWidth
              onChange={handleChange(agentIndex, 'value')}
              value={agentIndex}
              disabled
              InputProps={{
                inputProps: {
                  type: 'number',
                }
              }}
            />
            <CustomSelect
              disabled={isDisabled}
              className={classes.spaced}
              label='Scheduling Algorithm'
              name='sched_type'
              onChange={(event) => {
                handleChange(agentIndex, 'value')(event);
                setAgents(agents => ({
                  ...agents, // keep old agents (whole)...
                  [agentIndex]: {
                    ...agents[agentIndex], // keep already set properties...
                    ['msg_server_mode']: false // update new values
                  }
                }))
              }
              }
              value={(agents[agentIndex] !== undefined && agents[agentIndex].sched_type)}
              error={error[`Agent ${agentIndex + 1} Scheduling Algorithm`]}
              // helpertext={hasError && agents[agentIndex].sched_type === undefined ? 'Required' : undefined}
              options={constants.SchedTypeEnum}
            />
            {agents[agentIndex].sched_type === constants.SchedTypeEnum['RR'] &&
              <TextField
                id="quantum"
                name="quantum"
                className={classes.spaced}
                label="Quantum"
                helperText='slots'
                placeholder="0"
                margin="normal"
                fullWidth
                onChange={handleChange(agentIndex, 'value')}
                value={agents[agentIndex].quantum}
                error={error[`Agent ${agentIndex + 1} Quantum`] || agents[agentIndex].quantum < 0}
                helperText={agents[agentIndex].quantum < 0 ? 'Must be greater than or equal to 0' : undefined}
                InputProps={{
                  inputProps: {
                    type: 'number',
                    min: 0
                  }
                }}
              />}
            <FormControlLabel
              className={classes.spaced}
              control={
                <Switch
                  disabled={isDisabled || agents[agentIndex].sched_type !== constants.SchedTypeEnum['EDF']}
                  checked={(agents[agentIndex] !== undefined && agents[agentIndex].msg_server_mode) || false}
                  onChange={handleChange(agentIndex, 'checked')}
                  name='msg_server_mode'
                  value='msg_server_mode'
                  color="secondary"
                />
              }
              label="Message server mode"
            />
          </FormGroup>
        </Grid>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            {agents[agentIndex].msg_server_mode &&
              <>
                <CustomSelect
                  className={classes.spaced}
                  label='Message server type'
                  name='server_type'
                  onChange={handleChange(agentIndex, 'value')}
                  value={(agents[agentIndex] !== undefined && agents[agentIndex].server_type)}
                  options={constants.ServerTypeEnum}
                  disabled={agents[agentIndex] !== undefined && (!agents[agentIndex].msg_server_mode)}
                  error={error[`Agent ${agentIndex + 1} Message server type`]}
                // helpertext={hasError && agents[agentIndex].msg_server_mode && agents[agentIndex].server_type === undefined ? 'Required' : undefined}
                />
                <TextField
                  id="server_budget"
                  name="server_budget"
                  className={classes.spaced}
                  label="Budget"
                  placeholder="1"
                  margin="normal"
                  fullWidth
                  onChange={handleChange(agentIndex, 'value')}
                  value={agents[agentIndex].server_budget || ''}
                  error={error[`Agent ${agentIndex + 1} Message server budget`] || Number(agents[agentIndex].server_budget) < 0 ||  (Number(agents[agentIndex].server_budget) > Number(agents[agentIndex].server_period))}
                  helperText={(Number(agents[agentIndex].server_budget) < 0 ||  (Number(agents[agentIndex].server_budget) > Number(agents[agentIndex].server_period))) ? 'Must be less than period and greater than 0' : undefined}
                  InputProps={{
                    inputProps: {
                      type: 'number',
                      min: 1,
                      max: 100,
                    }
                  }}
                />
                <TextField
                  id="server_period"
                  name="server_period"
                  className={classes.spaced}
                  label="Period"
                  placeholder="1"
                  margin="normal"
                  fullWidth
                  onChange={handleChange(agentIndex, 'value')}
                  value={agents[agentIndex].server_period || ''}
                  error={error[`Agent ${agentIndex + 1} Message server period`] || Number(agents[agentIndex].server_period) < 0 ||  (Number(agents[agentIndex].server_budget) > Number(agents[agentIndex].server_period))}
                  helperText={(Number(agents[agentIndex].server_period) < 0 ||  (Number(agents[agentIndex].server_budget) > Number(agents[agentIndex].server_period))) ? 'Must be greater than budget and greater than 0' : undefined}
                  InputProps={{
                    inputProps: {
                      type: 'number',
                      min: 1,
                      max: 100,
                    }
                  }}
                />
              </>
            }

          </FormGroup>
        </Grid>
      </Grid>
    </div>
  )
}