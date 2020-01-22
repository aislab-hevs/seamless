import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import CustomSelect from './CustomSelect';
import * as constants from '../../utils/constants';
import {
  TextField,
  FormLabel,
  FormGroup,
  FormControl,
  Select,
  MenuItem,
  InputLabel,
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

export default function ServerForm(props) {
  const { rt_agents, agents_n, setServers, servers, serverIndex, error } = props;
  const classes = useStyles();

  // Dark magic here
  const handleChange = index => event => {
    event.persist();
    if (!servers[index]) servers[index] = {};
    setServers(servers => ({
      ...servers, // keep old servers (whole)...
      [index]: {
        ...servers[index], // keep already set properties...
        [event.target.name]: event.target.value // update new values
      }
    }));
  };

  const getRTAgentsMenuItems = () => {
    let options = [];
    for (let ag of rt_agents) {
      options.push(<MenuItem
        key={ag}
        value={`${ag}`}>{ag}
      </MenuItem>)
    }
    return options;
  }

  return (
    <div className={classes.root}>
      <FormLabel component="legend">Server Configuration</FormLabel>
      <Grid container spacing={4}>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            <FormControl className={classes.spaced}>
              <InputLabel error={error[`Server ${serverIndex + 1} Agent Id`]} htmlFor='agent_id'>Agent Id</InputLabel>
              <Select
                value={(servers[serverIndex] && servers[serverIndex].agent_id) || ''}
                error={error[`Server ${serverIndex + 1} Agent Id`]}
                onChange={handleChange(serverIndex)}
                inputProps={{
                  name: `agent_id`,
                  id: `agent_id`,
                }}
                MenuProps={MenuProps}
              >
                {rt_agents.length === Number(agents_n) && <MenuItem value={"-1"}>All</MenuItem>}
                {getRTAgentsMenuItems()}
              </Select>
            </FormControl>
            <TextField
              id="server_id"
              name="server_id"
              className={classes.spaced}
              label="Server Id"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(serverIndex)}
              value={(servers[serverIndex] && servers[serverIndex].server_id) || ''}
              error={error[`Server ${serverIndex + 1} Id`]}
              // helperText={hasError && servers[serverIndex].server_id === undefined ? 'Required' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
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
              onChange={handleChange(serverIndex)}
              value={(servers[serverIndex] && servers[serverIndex].period) || ''}
              error={error[`Server ${serverIndex + 1} Period`] || (servers[serverIndex] && (Number(servers[serverIndex].period) < 1) || (Number(servers[serverIndex].period) < Number(servers[serverIndex].budget)))}
              helperText={(servers[serverIndex] && ((Number(servers[serverIndex].period) < 1) || (Number(servers[serverIndex].period) < Number(servers[serverIndex].budget)))) ? 'Must be greater than budget and greater than 1' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 10000,
                }
              }}
            />
            <TextField
              id="budget"
              name="budget"
              className={classes.spaced}
              label="Budget"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(serverIndex)}
              value={(servers[serverIndex] && servers[serverIndex].budget) || ''}
              error={error[`Server ${serverIndex + 1} Budget`] || (servers[serverIndex] && (Number(servers[serverIndex].budget) < 1) || (Number(servers[serverIndex].period) < Number(servers[serverIndex].budget)))}
              helperText={(servers[serverIndex] && ((Number(servers[serverIndex].budget) < 1) || (Number(servers[serverIndex].period) < Number(servers[serverIndex].budget)))) ? 'Must be less than period and greater than 1' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <CustomSelect
              className={classes.spaced}
              label='Server type'
              name='type'
              onChange={handleChange(serverIndex)}
              value={servers[serverIndex] && servers[serverIndex].type}
              error={error[`Server ${serverIndex + 1} Type`]}
              options={constants.ServerTypeEnum}
            />
          </FormGroup>
        </Grid>
      </Grid>
    </div>
  )
}