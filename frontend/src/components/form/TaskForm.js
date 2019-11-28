import React, { useEffect } from 'react';
import { makeStyles } from '@material-ui/core/styles';
import {
  TextField,
  FormLabel,
  FormGroup,
  FormControl,
  Select,
  MenuItem,
  InputLabel,
  FormControlLabel,
  Switch,
  Grid
} from '@material-ui/core';

const useStyles = makeStyles(theme => ({
  spaced: {
    margin: theme.spacing(1),
    maxWidth: 240,
  }
}));

const ITEM_HEIGHT = 48;
const ITEM_PADDING_TOP = 8;
const MenuProps = {
  PaperProps: {
    style: {
      maxHeight: ITEM_HEIGHT * 4.5 + ITEM_PADDING_TOP,
      width: 250,
    },
  },
};

export default function TaskForm(props) {
  const { getAgentsMenuItems, setKnowledge, knowledge, taskIndex, servers, error } = props;
  const classes = useStyles();

  // Dark magic here
  const handleChange = (index, prop) => event => {
    event.persist();
    if (!knowledge[index]) knowledge[index] = {};
    setKnowledge(knowledge => ({
      ...knowledge, // keep old knowledge (whole)...
      [index]: {
        ...knowledge[index], // keep already set properties...
        [event.target.name]: event.target[prop] // update new values
      }
    }));
  };

  const initValue = (param, value) => {
    if (knowledge[taskIndex])
      knowledge[taskIndex][param] = knowledge[taskIndex][param] !== undefined
        ? knowledge[taskIndex][param]
        : value;
  }

  //  const idExists = () => {
  //    return 
  //  }

  useEffect(() => {
    initValue('isPublic', false);
    initValue('inTaskset', false);
    initValue('server', '-1');
    initValue('n_exec', '-1');
    initValue('firstActivationTime', '-1');
    initValue('lastActivationTime', '-1')
  }, [taskIndex]) // initialize isPublic to false as default (for each new task!)

  const getServers = () => {
    const available = [];
    if (Object.keys(servers).length > 0) {
      Object.keys(servers).forEach(index => {
        if (servers[index].agent_id === '-1' ||
          (knowledge[taskIndex] !== undefined && servers[index].agent_id === knowledge[taskIndex].agentExecutor))
          available.push(servers[index].server_id)
      });
    }
    return [...new Set(available)]; // delete duplicates (there should be no need because servers should have unique id!)
  }

  return (
    <div className={classes.root}>
      <FormLabel component="legend">Knowledge Configuration</FormLabel>
      <Grid container spacing={4}>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            <TextField
              id="id"
              name="id"
              className={classes.spaced}
              label="Id"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].id) || ''}
              error={error[`Task ${taskIndex + 1} Id`]}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <FormControl className={classes.spaced}>
              <InputLabel error={error[`Task ${taskIndex + 1} Agent Executor`]} htmlFor='agentExecutor'>Agent Executor</InputLabel>
              <Select
                value={(knowledge[taskIndex] && knowledge[taskIndex].agentExecutor) || ''}
                error={error[`Task ${taskIndex + 1} Agent Executor`]}
                onChange={handleChange(taskIndex, 'value')}
                inputProps={{
                  name: `agentExecutor`,
                  id: `agentExecutor`,
                }}
                MenuProps={MenuProps}
              >
                <MenuItem value={-1}>All</MenuItem>
                {getAgentsMenuItems()}
              </Select>
            </FormControl>
            <FormControl className={classes.spaced}>
              <InputLabel error={error[`Task ${taskIndex + 1} Agent Demander`]} htmlFor='agentDemander'>Agent Demander</InputLabel>
              <Select
                value={(knowledge[taskIndex] && knowledge[taskIndex].agentDemander) || ''}
                error={error[`Task ${taskIndex + 1} Agent Demander`]}
                onChange={handleChange(taskIndex, 'value')}
                inputProps={{
                  name: `agentDemander`,
                  id: `agentDemander`,
                }}
                MenuProps={MenuProps}
              >
                <MenuItem value={-1}>All</MenuItem>
                {getAgentsMenuItems()}
              </Select>
            </FormControl>
            <TextField
              id="computationTime"
              name="computationTime"
              className={classes.spaced}
              label="Computation Time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].computationTime) || ''}
              error={error[`Task ${taskIndex + 1} Computation Time`] || (knowledge[taskIndex] && Number(knowledge[taskIndex].computationTime) < 1)}
              helperText={(knowledge[taskIndex] && Number(knowledge[taskIndex].computationTime) < 1) ? 'Must be greater than 0' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="residualComputationTime"
              name="residualComputationTime"
              className={classes.spaced}
              label="Residual Computation Time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].residualComputationTime) || ''}
              error={error[`Task ${taskIndex + 1} Residual Computation Time`] || (knowledge[taskIndex] && (Number(knowledge[taskIndex].residualComputationTime) > Number(knowledge[taskIndex].computationTime)))}
              helperText={(knowledge[taskIndex] && (Number(knowledge[taskIndex].residualComputationTime) > Number(knowledge[taskIndex].computationTime))) ? 'Must be lesser than or equal to computation time' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="arrivalTime"
              name="arrivalTime"
              className={classes.spaced}
              label="Arrival Time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].arrivalTime) || ''}
              error={error[`Task ${taskIndex + 1} Arrival Time`] || (knowledge[taskIndex] && (Number(knowledge[taskIndex].arrivalTime) < 0))}
              helperText={(knowledge[taskIndex] && (Number(knowledge[taskIndex].arrivalTime) < 0)) ? 'Must be positive' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <FormControlLabel
              className={classes.spaced}
              control={
                <Switch
                  checked={(knowledge[taskIndex] && knowledge[taskIndex].isPublic) || false}
                  onChange={handleChange(taskIndex, 'checked')}
                  name='isPublic'
                  value='isPublic'
                  color="secondary"
                />
              }
              label="Public"
            />
          </FormGroup>
        </Grid>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            <TextField
              id="period"
              name="period"
              className={classes.spaced}
              label="Period"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].period) || ''}
              error={error[`Task ${taskIndex + 1} Period`] || (knowledge[taskIndex] && Number(knowledge[taskIndex].period) < Number(knowledge[taskIndex].computationTime))}
              helperText={(knowledge[taskIndex] && (Number(knowledge[taskIndex].period) < Number(knowledge[taskIndex].computationTime))) ? 'Must be greater than computation time' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="relativeDeadline"
              name="relativeDeadline"
              className={classes.spaced}
              label="Relative Deadline"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].relativeDeadline) || ''}
              error={error[`Task ${taskIndex + 1} Relative Deadline`] || (knowledge[taskIndex] && (Number(knowledge[taskIndex].relativeDeadline) < Number(knowledge[taskIndex].period)))}
              helperText={(knowledge[taskIndex] && (Number(knowledge[taskIndex].relativeDeadline) < Number(knowledge[taskIndex].period))) ? 'Must be greater than or equal to the period' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="n_exec"
              name="n_exec"
              className={classes.spaced}
              label="Number of executions"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].n_exec) || ''}
              error={error[`Task ${taskIndex + 1} Number of executions`]}
              helperText={'Leave -1 to have indefinite executions'}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="firstActivationTime"
              name="firstActivationTime"
              className={classes.spaced}
              label="First Activation Time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].firstActivationTime) || ''}
              error={error[`Task ${taskIndex + 1} First Activation Time`]}
              helperText={'Leave -1 to let the simulator handle it'}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="lastActivationTime"
              name="lastActivationTime"
              className={classes.spaced}
              label="Last Activation Time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(taskIndex, 'value')}
              value={(knowledge[taskIndex] && knowledge[taskIndex].lastActivationTime) || ''}
              error={error[`Task ${taskIndex + 1} Last Activation Time`]}
              helperText={'Leave -1 to let the simulator handle it'}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <FormControl className={classes.spaced}>
              <InputLabel error={error[`Task ${taskIndex + 1} Server`]} htmlFor='server'>Server</InputLabel>
              <Select
                value={(knowledge[taskIndex] && knowledge[taskIndex].server) || []}
                error={error[`Task ${taskIndex + 1} Server`]}
                onChange={handleChange(taskIndex, 'value')}
                inputProps={{
                  name: `server`,
                  id: `server`,
                }}
                MenuProps={MenuProps}
              >
                <MenuItem value={'-1'}>None</MenuItem>
                {getServers().map((server, index) => {
                  return server !== undefined && <MenuItem
                    key={index}
                    value={server}>{server}
                  </MenuItem>
                })}
              </Select>
            </FormControl>
            <FormControlLabel
              className={classes.spaced}
              control={
                <Switch
                  checked={(knowledge[taskIndex] && knowledge[taskIndex].inTaskset) || false}
                  onChange={handleChange(taskIndex, 'checked')}
                  name='inTaskset'
                  value='inTaskset'
                  color="secondary"
                />
              }
              label="Add to taskset"
            />
          </FormGroup>
        </Grid>
      </Grid>
    </div>
  )
}