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