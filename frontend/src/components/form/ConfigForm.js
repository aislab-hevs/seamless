import React, { useState, useEffect } from 'react';
import 'date-fns';
import DateFnsUtils from '@date-io/date-fns';
import { makeStyles } from '@material-ui/core/styles';
import CustomSelect from './CustomSelect';
import {
  TextField,
  Box,
  Grid,
  FormLabel,
  FormControlLabel,
  Switch,
  FormGroup,
} from '@material-ui/core';
import { MuiPickersUtilsProvider, KeyboardDatePicker } from '@material-ui/pickers';
import * as constants from '../../utils/constants';

const useStyles = makeStyles(theme => ({
  root: {
    width: '90%',
  },
  spaced: {
    margin: theme.spacing(1),
    maxWidth: 300,
  }
}));

export default function ConfigForm(props) {
  const classes = useStyles();
  const [selectedDate, setSelectedDate] = useState(new Date());
  const { handleChange, handleSubmit, values, error } = props;

  const initValue = (param, value) => {
    values[param] = values[param] !== undefined
      ? values[param]
      : value;
  }

  useEffect(() => {
    values.date = new Date().toISOString();
    initValue('apply_for_all', false);
    initValue('use_neg', false);
    initValue('DF_msg_server_mode', false);
    initValue('msg_server_mode', false);
    // initValue('DF_server_type', -1);
    // initValue('server_type', -1);
    // initValue('neg_type', -1); // moved in backend parser
    // initValue('contr_h', -1); // moved in backend parser
    // initValue('bidder_h', -1); // moved in backend parser
    // initValue('neg_timeout', 0); // moved in backend parser
  }); // initialize default values

  function handleDateChange(date) {
    setSelectedDate(date);
  }

  return (
    <div className={classes.root}>
      <Box>
        <Grid container className={classes.root} spacing={4}>
          <Grid item xs={12} sm={6} md={4}>
            <FormLabel component="legend">Simulator Options</FormLabel>
            <FormGroup>
              <MuiPickersUtilsProvider utils={DateFnsUtils}>
                <KeyboardDatePicker
                  className={classes.spaced}
                  disableToolbar
                  disabled
                  variant="inline"
                  format="MM/dd/yyyy"
                  margin="normal"
                  id="sim-date"
                  label="Simulation Date"
                  value={values.date}
                  onChange={handleDateChange}
                  KeyboardButtonProps={{
                    'aria-label': 'change date',
                  }}
                />
              </MuiPickersUtilsProvider>
              <TextField
                id="agents_n"
                name="agents_n"
                className={classes.spaced}
                label="Number of agents"
                placeholder="1"
                margin="normal"
                fullWidth
                onChange={handleChange('value')}
                value={values.agents_n || ''}
                error={error['Number of agents'] || values.agents_n < 1}
                helperText={values.agents_n < 1 ? 'Must be greater than 0' : undefined}
                InputProps={{
                  inputProps: {
                    type: 'number',
                    min: 1,
                    max: 100,
                  }
                }}
              />
              <TextField
                id="min_delay"
                name="min_delay"
                className={classes.spaced}
                label="Minimum channel delay"
                placeholder="0"
                margin="normal"
                fullWidth
                onChange={handleChange('value')}
                value={values.min_delay || ''}
                error={error['Minimum channel delay'] || values.min_delay < 0}
                helperText={values.min_delay < 0 ? 'Must be greater than or equal to 0' : 'milliseconds'}
                InputProps={{
                  inputProps: {
                    type: 'number',
                    min: 0,
                    max: 1000
                  }
                }}
              />
              <TextField
                id="max_delay"
                name="max_delay"
                className={classes.spaced}
                label="Maximum channel delay"
                placeholder="0"
                margin="normal"
                fullWidth
                onChange={handleChange('value')}
                value={values.max_delay || ''}
                error={error['Maximum channel delay'] || Number(values.max_delay) < Number(values.min_delay)}
                helperText={Number(values.max_delay) < Number(values.min_delay) ? 'Must be greater than or equal to minimum delay' : 'milliseconds'}
                InputProps={{
                  inputProps: {
                    type: 'number',
                    min: 0,
                    max: 1000
                  }
                }}
              />
              <TextField
                id="time"
                name="time"
                className={classes.spaced}
                label="Simulation Time"
                placeholder="1"
                margin="normal"
                fullWidth
                onChange={handleChange('value')}
                value={values.time || ''}
                error={error['Simulation Time'] || values.time < 1}
                helperText={values.time < 1 ? 'Must be greater than 0' : 'seconds'}
                InputProps={{
                  inputProps: {
                    type: 'number',
                    min: 1,
                    max: 10000
                  }
                }}
              />
            </FormGroup>
          </Grid>
          <Grid item xs={12} sm={6} md={4}>
            <FormLabel component="legend">Agents Options</FormLabel>
            <FormGroup>
              <CustomSelect
                shrinked={values.DF_sched_type !== undefined ? 1 : 0} // workaround to error 'received value for non-boolean attribute
                className={classes.spaced}
                label='DF Scheduling Algorithm'
                name='DF_sched_type'
                onChange={handleChange('value')}
                value={values.DF_sched_type}
                error={error['DF Scheduling Algorithm']}
                helpertext={error.DF_sched_type ? 'Required' : undefined}
                options={constants.SchedTypeEnum}
              />
              {values.DF_sched_type === 1 &&
                <TextField
                  id="DF_quantum"
                  name="DF_quantum"
                  className={classes.spaced}
                  label="Quantum"
                  placeholder="0"
                  margin="normal"
                  fullWidth
                  onChange={handleChange('value')}
                  value={values.DF_quantum || ''}
                  error={error['DF quantum'] || values.DF_quantum < 0}
                  helperText={values.DF_quantum < 0 ? 'Must be greater than 0' : 'Time slots'}
                  InputProps={{
                    inputProps: {
                      type: 'number',
                      min: 0,
                      max: values.time
                    }
                  }}
                />}
              <FormControlLabel
                className={classes.spaced}
                control={
                  <Switch
                    checked={values.DF_msg_server_mode || false}
                    onChange={handleChange('checked')}
                    name='DF_msg_server_mode'
                    value='DF_msg_server_mode'
                    color="secondary"
                  />
                }
                label="DF Message server mode"
              />
              <CustomSelect
                className={classes.spaced}
                label='DF Message server type'
                name='DF_server_type'
                onChange={handleChange('value')}
                value={values.DF_server_type}
                options={constants.ServerTypeEnum}
                disabled={!values.DF_msg_server_mode}
                error={error['DF Message server type'] || error.DF_server_type}
                // helpertext={error.DF_server_type ? 'Required' : undefined}
              />
              <FormControlLabel
                className={classes.spaced}
                control={
                  <Switch
                    checked={values.apply_for_all || false}
                    onChange={handleChange('checked')}
                    name='apply_for_all'
                    value='apply_for_all'
                    color="secondary"
                  />
                }
                label="Apply for every agent"
              />
              {values.apply_for_all &&
                <>
                  <CustomSelect
                    className={classes.spaced}
                    label='Scheduling Algorithm'
                    name='sched_type'
                    onChange={handleChange('value')}
                    value={values.sched_type}
                    error={error['Scheduling Algorithm']}
                    // helpertext={error.sched_type ? 'Required' : undefined}
                    options={constants.SchedTypeEnum}
                  />
                  {values.sched_type === 1 &&
                    <TextField
                      id="quantum"
                      name="quantum"
                      className={classes.spaced}
                      label="Quantum"
                      helperText='slots'
                      placeholder="0"
                      margin="normal"
                      fullWidth
                      onChange={handleChange('value')}
                      value={values.quantum || ''}
                      error={error['Quantum'] || values.quantum < 0}
                      InputProps={{
                        inputProps: {
                          type: 'number',
                          min: 0,
                          max: values.time
                        }
                      }}
                    />}
                  <FormControlLabel
                    className={classes.spaced}
                    control={
                      <Switch
                        checked={values.msg_server_mode || false}
                        onChange={handleChange('checked')}
                        name='msg_server_mode'
                        value='msg_server_mode'
                        color="secondary"
                      />
                    }
                    label="Message server mode"
                  />
                  <CustomSelect
                    className={classes.spaced}
                    label='Message server type'
                    name='server_type'
                    onChange={handleChange('value')}
                    value={values.server_type}
                    error={error['Message server type']}
                    // helpertext={error.server_type ? 'Required' : undefined}
                    options={constants.ServerTypeEnum}
                    disabled={!values.msg_server_mode}
                  />
                </>}
            </FormGroup>
          </Grid>
          <Grid item xs={12} sm={6} md={4}>
            <FormLabel component="legend">Negotiation Options</FormLabel>
            <FormGroup>
              <FormControlLabel
                className={classes.spaced}
                control={
                  <Switch
                    checked={values.use_neg || false}
                    onChange={handleChange('checked')}
                    name='use_neg'
                    value='use_neg'
                    color="secondary"
                  />
                }
                label="Use negotiation"
              />
              {values.use_neg &&
                <>
                  <CustomSelect
                    className={classes.spaced}
                    label='Negotiation Protocol'
                    name='neg_type'
                    onChange={handleChange('value')}
                    value={values.neg_type}
                    error={error['Negotiation Protocol']}
                    // helpertext={hasError && values.use_neg && values.neg_type === undefined ? 'Required' : undefined}
                    options={constants.NegTypeEnum}
                  />
                  <CustomSelect
                    className={classes.spaced}
                    label='Contractor Heuristic'
                    name='contr_h'
                    onChange={handleChange('value')}
                    value={values.contr_h}
                    error={error['Contractor Heuristic'] }
                    // helpertext={hasError && values.use_neg && values.contr_h === undefined ? 'Required' : undefined}
                    options={constants.ContractorPoliciesEnum}
                  />
                  <CustomSelect
                    className={classes.spaced}
                    label='Bidder Heuristic'
                    name='bidder_h'
                    onChange={handleChange('value')}
                    value={values.bidder_h}
                    error={error['Bidder Heuristic']}
                    // helpertext={hasError && values.use_neg && values.bidder_h === undefined ? 'Required' : undefined}
                    options={constants.BidderPoliciesEnum}
                  />
                  {/* <TextField
                    id="neg_timeout"
                    name="neg_timeout"
                    className={classes.spaced}
                    label="Bidding window"
                    helperText="seconds"
                    placeholder="0"
                    margin="normal"
                    fullWidth
                    onChange={handleChange('value')}
                    value={values.neg_timeout || ''}
                    error={error['Bidding window'] || values.neg_timeout < 0}
                    helperText={values.neg_timeout < 0 ? 'Must be greater than or equal to 0' : undefined}
                    InputProps={{
                      inputProps: {
                        type: 'number',
                        min: 0,
                      }
                    }}
                  /> */}
                </>}
            </FormGroup>
          </Grid>
        </Grid>
      </Box>
    </div>
  );
}

//NOTES
// .1: Consider the poossibility to not use negotiation -> no need for heuristics!