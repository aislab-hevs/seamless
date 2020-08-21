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

import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import {
  Button
} from '@material-ui/core';
import * as constants from '../../utils/constants';

const useStyles = makeStyles(theme => ({
  button: {
    margin: theme.spacing(1),
  },
}));

export default function HistoryButtons(props) {
  const { structure, setStructure, setStructureIndex, header, activeStep, structureIndex, error, setError } = props
  const classes = useStyles();

  // perform a check before allowing to add tasks!
  const handleAdd = () => {
    let newIndex = Object.keys(structure).length;
    structure[newIndex] = {};
    setStructureIndex(newIndex);
  }

  const handleDelete = () => {
    clearError();
    if (structureIndex >= 0) {
      for (let i = structureIndex; i < Object.keys(structure).length - 1; i++) {
        structure[i] = structure[i + 1];
      }
      delete structure[Object.keys(structure).length - 1];
      setStructure(structure => ({ ...structure }));
      setStructureIndex(Object.keys(structure).length - 1);
    }
  }

  const clearError = () => {
    let name = header.charAt(0) + header.slice(1).toLowerCase().slice(0, header.length - 2);
    for (let key in error) {
      if (key.includes(`${name}`)) delete error[key] //if (key.includes(`${name} ${structureIndex + 1}`)) delete error[key]
    }
    setError(error => ({ ...error }));
  }

  const getColor = index => {
    switch (header) {
      case 'TASKS': {
        if (structure[index].agentExecutor === '-1')  return 'grey'
        else return constants.colors[Number(structure[index].agentExecutor) % constants.colors.length];
      }
      case 'SERVERS':
      case 'NEEDS': {
        if (structure[index].agent_id === '-1') return 'grey'
        else return structure[index].agent_id
          ? constants.colors[Number(structure[index].agent_id) % constants.colors.length]
          : constants.colors[0];
      }
      default: return constants.colors[index % constants.colors.length];
    }
  }

  const getId = index => {
    switch (header) {
      case 'SERVERS':
        return structure[index].server_id || '-';
      case 'TASKS':
        return structure[index].id || '-';
      default: return index;
    }
  }

  return (
    <>
      <h3>{header}</h3>
      {Object.keys(structure).map((key, index) => {
        return <Button
          className={classes.button}
          key={`task-${key}`}
          variant="contained"
          onClick={() => setStructureIndex(index)}
          style={{ backgroundColor: `${getColor(index)}`, color: '#ffffff' }}
          color='primary'
        >
          {/* {index + 1} */}
          {getId(index)}
        </Button>
      })}
      {activeStep !== 1 &&
        <Button
          className={classes.button}
          variant="contained"
          // style={{ backgroundColor: constants.colors[2], color: '#ffffff' }}
          onClick={handleAdd}>
          Add
      </Button>}
      {activeStep !== 1 &&
        <Button
          disabled={Object.keys(structure).length === 1}
          className={classes.button}
          variant="contained"
          // color="secondary"
          onClick={handleDelete}>
          Del
      </Button>}
    </>
  )
}