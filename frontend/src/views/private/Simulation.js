/*
 * Copyright (c) 2020, HES-SO Valais-Wallis (https://www.hevs.ch)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

import React, { useState, useEffect } from 'react';
import Typography from '../../components/Typography';
import FormStepper from '../../components/FormStepper';
import ConfigForm from '../../components/form/ConfigForm';
import ComboForm from '../../components/form/ComboForm';
import useSessionStorage from '../../hooks/useSessionStorage';
import DialogWrapper from '../../components/DialogWrapper';
import Summary from '../../components/Summary';
import {
  Box
} from '@material-ui/core';
import useForm from '../../hooks/useForm';
import { navigate, useQueryParams } from 'hookrouter';
import * as api from '../../api/api';
import * as validator from '../../utils/validator';
import * as parser from '../../utils/inverseParser';
import * as constants from '../../utils/constants';

function Simulation(props) {
  const { user } = props;
  const [token] = useSessionStorage('token');
  const [activeStep, setActiveStep] = useState(0);
  const [agents, setAgents] = useState({ 0: {} });
  const [agentIndex, setAgentIndex] = useState(0);
  const [knowledge, setKnowledge] = useState({ 0: {} });
  const [taskIndex, setTaskIndex] = useState(0);
  const [servers, setServers] = useState({ 0: {} });
  const [serverIndex, setServerIndex] = useState(0);
  const [needs, setNeeds] = useState({ 0: {} });
  const [needIndex, setNeedIndex] = useState(0);
  const { handleChange, handleSubmit, values, setValues } = useForm();
  const [open, setOpen] = useState(false);
  const [summaryOpen, setSummaryOpen] = useState(false);
  const [message, setMessage] = useState('');
  const [error, setError] = useState({});
  const [ready, setReady] = useState(false);
  const [ignored, setIgnored] = useState(new Set());
  const [queryParams, setQueryParams] = useQueryParams();

  const getForm = () => ({
    '0': <ConfigForm
      handleChange={handleChange}
      handleSubmit={handleSubmit}
      values={values}
      setValues={setValues}
      error={error}
      rt_agents={getRTAgents()}
    />,
    '1': <ComboForm
      activeStep={activeStep}
      header='AGENTS'
      isDisabled={values.apply_for_all}
      agents_n={values.agents_n}
      structure={agents}
      setStructure={setAgents}
      structureIndex={agentIndex}
      setStructureIndex={setAgentIndex}
      error={error}
      setError={setError}
    />,
    '2': <ComboForm
      activeStep={activeStep}
      header='SERVERS'
      agents_n={values.agents_n}
      rt_agents={getRTAgents()}
      structure={servers}
      setStructure={setServers}
      structureIndex={serverIndex}
      setStructureIndex={setServerIndex}
      error={error}
      setError={setError}
    />,
    '3': <ComboForm
      activeStep={activeStep}
      header='TASKS'
      agents_n={values.agents_n}
      structure={knowledge}
      setStructure={setKnowledge}
      structureIndex={taskIndex}
      setStructureIndex={setTaskIndex}
      servers={servers}
      error={error}
      setError={setError}
    />,
    '4': <ComboForm
      activeStep={activeStep}
      header='NEEDS'
      agents_n={values.agents_n}
      structure={needs}
      setStructure={setNeeds}
      structureIndex={needIndex}
      setStructureIndex={setNeedIndex}
      tasks={knowledge}
      neg_type={values.neg_type}
      use_neg={values.use_neg}
      error={error}
      setError={setError}
    />,
  });

  const filterKnowledge = (knowledge) => {
    let taskset = {};
    Object.keys(knowledge).forEach(key => {
      if (knowledge[key].inTaskset === true) taskset[key] = Object.assign({}, knowledge[key]);
    });
    return taskset;
  }

  const validate = () => {
    validator.checkForms(ignored, values, agents, servers, knowledge, needs, error, setError);
    if (validator.isValid(error)) {
      setReady(true);
      return true;
    }
    return false
  }

  const formatError = error => {
    let err_string = 'Please fix the following fields: ';
    let length = Object.keys(error).length;
    Object.keys(error).forEach((key, i) => {
      if (error[key]) {
        err_string += `${key}`
        if (i < length - 1) err_string += `, `
        // else err_string += `.`
      }
      if (i === length - 1) {
        err_string = err_string.slice(0, err_string.length - 2);
        err_string += `.`;
      }
    });
    return err_string;
  }

  const getSkippable = activeStep => {
    switch (activeStep) {
      case 1: return values.apply_for_all
      case 2: return true
      case 4: return !values.use_neg
      default: return true;
    }
  }

  const getNextable = activeStep => {
    switch (activeStep) {
      case 1: return !values.apply_for_all
      case 2: return getRTAgents().length > 0;
      case 4: return values.use_neg
      default: return true;
    }
  }
  const getAgList = () => {
    return [...Object.keys(agents)];
  }

  const getRTAgents = () => {
    let rt_agents = [];
    if (values.apply_for_all && values.sched_type === constants.SchedTypeEnum['EDF']) {
      rt_agents = getAgList();
    } else {
      for (let key in agents) {
        if (agents[key].sched_type === constants.SchedTypeEnum['EDF']) rt_agents.push(key);
      }
    }
    return rt_agents;
  }

  const submitData = async () => {
    const valid = validate();
    //if valid do below else show error message with references
    if (valid) {
      const config = { user: user.email, ...values };
      const taskset = filterKnowledge(knowledge);
      const inputs = { agents, knowledge, taskset, servers, needs }
      let res = await api.runSimulation(config, inputs, token);
      if (res.includes('failed')) setReady(false);
      setMessage(res);
      setOpen(true);
    } else {
      // setup error message
      let msg = formatError(error);
      setMessage(msg);
      setOpen(true);
    }
  }

  const openSummary = () => {
    setSummaryOpen(true);
  }

  const handleClose = () => {
    setOpen(false);
  }

  const handleSummaryClose = () => {
    setSummaryOpen(false);
  }

  const handleView = () => {
    navigate(`/dashboard/history/analysis/${user.email}/${values.date}`);
  }

  const fetchSimulationConfig = async date => {
    const inputs = await api.getInputs(user.email, date, token);
    // inverse parse inputs and set them
    setKnowledge(parser.inverseParse(inputs.knowledge));
    setServers(parser.inverseParse(inputs.servers));
    setNeeds(parser.inverseParse(inputs.needs));
    setAgents(inputs.agents)
    let inv_config = parser.inverseParseConfig(inputs.config);
    setValues(values => ({ ...values, ...inv_config }));
  }

  useEffect(() => {
    //load simulation
    if (Object.keys(queryParams).length > 0) fetchSimulationConfig(queryParams.date)
  }, [queryParams]);

  return (
    <>
      <Box pb={2} pt={4}>
        <Typography variant='h2' className={props.classes.title}>
          Simulation
        </Typography>
      </Box>
      <Box pb={2} pt={4}>
        {getForm()[activeStep]}
        <FormStepper
          activeStep={activeStep}
          setActiveStep={setActiveStep}
          submitData={submitData}
          setIgnored={setIgnored}
          skippable={getSkippable(activeStep)}
          nextable={getNextable(activeStep)}
          openSummary={openSummary}
        />
      </Box>
      <DialogWrapper
        title='SUMMARY'
        open={summaryOpen}
        onClose={handleSummaryClose}
        maxWidth='lg'
        children={
          <Summary
            config={values}
            agents={agents}
            knowledge={knowledge}
            servers={servers}
            needs={needs}
            ids={getAgList()}
          />
        }
      />
      <DialogWrapper
        title={ready ? 'INFO' : 'ERROR'}
        open={open}
        onClose={handleClose}
        children={message}
        onView={handleView}
        ready={ready}
      />
    </>
  )
}

export default Simulation;