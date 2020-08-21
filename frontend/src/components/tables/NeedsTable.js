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
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Paper from '@material-ui/core/Paper';
import Tooltip from '@material-ui/core/Tooltip';

const useStyles = makeStyles(theme => ({
  root: {
    width: '100%',
    // width: 785
  },
  paper: {
    // marginTop: theme.spacing(3),
    width: '100%',
    overflowX: 'auto',
    // marginBottom: theme.spacing(2),
  },
  table: {
    // width: 785, // static
  },
}));

export default function NeedsTable(props) {
  const { needs } = props;
  const classes = useStyles();

  return (
    <div className={classes.root}>
      {needs.length > 0
        ? <Paper elevation={0} className={classes.paper}>
          <Table className={classes.table} size="small" aria-label="knowledge-table">
            <TableHead>
              <TableRow>
                <Tooltip title="Need id" placement="top"><TableCell align="right">Id</TableCell></Tooltip>
                <Tooltip title="Demander agent" placement="top"><TableCell align="right">Ag</TableCell></Tooltip>
                <Tooltip title="Need release time" placement="top"><TableCell align="right">R</TableCell></Tooltip>
                <Tooltip title="Bidding window" placement="top"><TableCell align="right">W</TableCell></Tooltip>
                <Tooltip title="Needed task(s) release time" placement="top"><TableCell align="right">TR</TableCell></Tooltip>
                <Tooltip title="Needed task(s) relative deadline" placement="top"><TableCell align="right">TD</TableCell></Tooltip>
                <Tooltip title="Needed task executions" placement="top"><TableCell align="right">n</TableCell></Tooltip>
                <Tooltip title="Needed minimum period (RBN)" placement="top"><TableCell align="right">MinT</TableCell></Tooltip>
                <Tooltip title="Needed maximum period (RBN)" placement="top"><TableCell align="right">MaxT</TableCell></Tooltip>
                <Tooltip title="Needed tasks" placement="top"><TableCell align="right">Tasks</TableCell></Tooltip>
              </TableRow>
            </TableHead>
            <TableBody>
              {needs.map((need, index) => (
                <TableRow key={index}>
                  <TableCell align="right">{index}</TableCell>
                  <TableCell align="right">{need.agent_id}</TableCell>
                  <TableCell align="right">{need.releaseTime}</TableCell>
                  <TableCell align="right">{need.neededTimeout}</TableCell>
                  <TableCell align="right">{need.neededTaskRelease}</TableCell>
                  <TableCell align="right">{need.neededTaskDeadline}</TableCell>
                  <TableCell align="right">{need.neededTaskNExec}</TableCell>
                  <TableCell align="right">{need.neededTaskTMin ? need.neededTaskTMin : '✗'}</TableCell>
                  <TableCell align="right">{need.neededTaskTMax ? need.neededTaskTMax : '✗'}</TableCell>
                  <TableCell align="right">{
                    need.neededTasks.map((task, i) => {
                      return i === need.neededTasks.length - 1 ? task : task + ', '
                    })
                  }</TableCell>
                </TableRow>
              ))}
            </TableBody>
          </Table>
        </Paper>
        : 'No needs.'
      }
    </div>
  );
}
