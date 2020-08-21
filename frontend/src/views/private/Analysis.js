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

import React, { useEffect, useState } from 'react'
import SimpleChart from '../../components/charts/SimpleChart'
import SimpleBarChart from '../../components/charts/SimpleBarChart'
import GanttScatterChart from '../../components/charts/GanttScatterChart';
import MergedUtilChart from '../../components/charts/MergedUtilChart';
import Typography from '../../components/Typography';
import Summary from '../../components/Summary';
import GetAppIcon from '@material-ui/icons/GetApp';
import {
  Paper,
  Box,
  Grid,
  FormControl,
  Select,
  MenuItem,
  Button,
  Tooltip
} from '@material-ui/core';
import Loading from '../../components/Loading';
import { makeStyles } from '@material-ui/styles';
import useSessionStorage from '../../hooks/useSessionStorage';
import * as api from '../../api/api';
import * as constants from '../../utils/constants';
import * as parser from '../../utils/inverseParser';

const useStyles = makeStyles(theme => ({
  divider: {
    border: `solid ${theme.palette.secondary.dark}`,
    // color: `${theme.palette.secondary.dark}`,
    marginLeft: theme.spacing(-2),
    marginBottom: theme.spacing(4),
  },
  responsive: {
    overflowX: 'auto',
    overflowY: 'hidden',
  },
  '@global': {
    '.MuiPaper-root': {
      overflowX: 'auto',
      overflowY: 'hidden',
    },
    '.MuiButtonBase-root': {
      minWidth: '36px'
    }
  },
  download: {
    marginLeft: theme.spacing(2),
    marginBottom: theme.spacing(0.7),
  }
}))

function Analysis(props) {
  const { user, run } = props;
  const [reports, setReports] = useState({});
  const [inputs, setInputs] = useState({});
  const [log, setLog] = useState({});
  const [agentIndex, setAgentIndex] = useState(0);
  const [token] = useSessionStorage('token');
  const [loading, setLoading] = useState(true);
  const classes = useStyles();

  const handleChange = event => {
    setAgentIndex(event.target.value);
  };

  const getTaskList = (agent) => {
    return reports.global_resp_time[agent] ? [...new Set(reports.global_resp_time[agent].map(entry => entry.taskId))] : [];
  }

  const getAgList = () => {
    return [...reports.stats.keys()];
  }

  const fetchReports = async (user, date, auth) => {
    if (user && date) {
      const data = await api.getReports(user, date, auth)
      return new Promise((resolve, reject) => {
        if (data) resolve(data);
      })
    }
  }

  const fetchLog = async (user, date, auth) => {
    if (user && date) {
      const data = await api.getLog(user, date, auth)
      return new Promise((resolve, reject) => {
        if (data) resolve(data);
      })
    }
  }

  const fetchSimulationConfig = async (user, date, auth) => {
    if (user && date) {
      const data = await api.getInputs(user, date, auth);
      return new Promise((resolve, reject) => {
        if (data) resolve(data);
      })
    }
  }

  const fetchSimulationFiles = async (user, date, auth) => {
    if (user && date) {
      const blob = await api.getSimulationFiles(user, date, auth);
      // Create an object URL for the blob object
      const url = URL.createObjectURL(blob);
      // Create a new anchor element
      const link = document.createElement('a');
      // Set the href and download attributes for the anchor element
      link.href = url;
      link.download = 'simulation.tar.gz';
      // document.body.appendChild(link);
      // Programmatically trigger a click on the anchor element
      // Useful if you want the download to happen automatically
      // Without attaching the anchor element to the DOM
      link.click();
      // link.parentNode.removeChild(link);
      // Return the anchor element
      // Useful if you want a reference to the element
      // in order to attach it to the DOM or use it in some other way
      return link;
    }
  }


  const handleDownload = () => {
    fetchSimulationFiles(user, run, token);
  }

  const fetchData = async (user, date, auth) => {
    const reports = await fetchReports(user, date, auth);
    const log = await fetchLog(user, date, auth);
    const settings = await fetchSimulationConfig(user, date, auth);
    setInputs({
      knowledge: parser.inverseParse(settings.knowledge),
      servers: parser.inverseParse(settings.servers),
      needs: parser.inverseParse(settings.needs),
      agents: settings.agents,
      config: parser.inverseParseConfig(settings.config),
    })
    setReports(reports);
    setLog(log);
    setLoading(false);
  }

  const getMaxBudget = data => {
    let max = 3; // minimum for readability is 3
    if (data) {
      Object.keys(data).forEach(key => {
        if (key.includes('S')) {
          for (let entry of data[key]) {
            if (entry.budget > max) {
              max = entry.budget;
              break;
            }
          }
        }
      })
    }
    return max;
  }

  useEffect(() => {
    const abortController = new AbortController();
    fetchData(user, run, token);
    return () => { abortController.abort() }; //cleanup async calls
  }, [token]);

  return (loading
    ? <Loading />
    : <>
      <Box pb={4} pt={4}>
        <Typography variant='h4'>
          Summary
          <span>
            <Tooltip title='Download' placement='top'>
              <Button onClick={handleDownload} variant='contained' color="secondary" size='small' className={classes.download}>
                <GetAppIcon fontSize='small' style={{ width: '20px' }} />
              </Button>
            </Tooltip>
          </span>
        </Typography>
      </Box>
      <Box pb={4}>
        <Summary
          date={run}
          config={inputs.config}
          agents={inputs.agents}
          knowledge={inputs.knowledge}
          servers={inputs.servers}
          needs={inputs.needs}
          ids={[...Object.keys(inputs.agents)]}
        />
      </Box>
      <Box pb={4} pt={4}>
        <Typography variant='h4'>
          Results
        </Typography>
      </Box>
      <Box p={2} >
        <hr className={classes.divider} />
        <h1>Global Statistics</h1>
      </Box>
      <Grid container spacing={3} style={{ marginBottom: '50px' }}>
        {reports.global_util &&
          <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agents_util">
                    Agents Utilization
              </Typography>
                </Box>
                {/* <Box className={classes.responsive}> */}
                <SimpleChart
                  dot={false}
                  multiline
                  colors={constants.colors}
                  field='time'
                  width={900}
                  height={300}
                  data={reports.global_util}
                  ids={getAgList()}
                  type="step"
                  value='ag_' />
                {/* </Box> */}
              </Grid>
            </Paper>
          </Box>
        }
        {reports.global_dmr &&
          <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agents_dmr">
                    Deadline Miss Ratio
              </Typography>
                </Box>
                <SimpleBarChart
                  data={reports.global_dmr}
                  colors={constants.colors}
                  field="dmr"
                  width={900}
                  height={300} />
              </Grid>
            </Paper>
          </Box>}
        {(inputs.config.use_neg && reports.global_acc_ratio)
          && <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agents_ddl_miss">
                    Acceptance ratio
              </Typography>
                </Box>
                <SimpleBarChart
                  data={reports.global_acc_ratio}
                  colors={constants.colors}
                  field="acceptance"
                  width={900}
                  height={300} />
              </Grid>
            </Paper>
          </Box>}
      </Grid>
      <Box p={2} >
        <hr className={classes.divider} />
        <h1>Local Statistics</h1>
        <FormControl>
          <Select
            value={agentIndex}
            onChange={handleChange}
            inputProps={{
              name: 'agentIndex',
              id: 'agentIndex',
            }}
          >
            {getAgList().map((key, index) => {
              return <MenuItem
                key={index}
                value={key}>Agent {key}
              </MenuItem>
            })}
          </Select>
        </FormControl>
      </Box>
      <Grid container spacing={3} style={{ marginBottom: '50px' }}>
        {reports.merged_util
          ? <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agent_util">
                    Utilization
              </Typography>
                </Box>
                <MergedUtilChart
                  colors={constants.colors}
                  width={900}
                  height={300}
                  data={reports.merged_util[agentIndex]}
                />
              </Grid>
            </Paper>
          </Box>
          : reports.util
          && <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agent_util">
                    Utilization
              </Typography>
                </Box>
                <SimpleChart
                  dot={false}
                  colors={constants.colors}
                  field='time'
                  width={900}
                  height={300}
                  data={reports.util[agentIndex]}
                  type="step"
                  value='utilization' />
              </Grid>
            </Paper>
          </Box>
        }
        {reports.local_dmr && reports.local_dmr[agentIndex] &&
          <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agents_ddl_miss">
                    Local Deadline Miss Ratio
              </Typography>
                </Box>
                <SimpleBarChart
                  // keys={['miss', 'checks']}
                  data={reports.local_dmr[agentIndex]}
                  colors={constants.colors}
                  field='dmr'
                  width={900}
                  height={300} />
              </Grid>
            </Paper>
          </Box>}
        {(reports.local_resp_time && reports.local_resp_time[agentIndex])
          &&
          <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agent_resp_time">
                    Response Time
              </Typography>
                </Box>
                <SimpleChart
                  dot={true}
                  multiline
                  colors={constants.colors}
                  field='time'
                  width={900}
                  height={300}
                  data={reports.local_resp_time[agentIndex]}
                  ids={getTaskList(agentIndex)} // insert taskset here
                  type="monotone"
                  value='t_' />
              </Grid>
            </Paper>
          </Box>}
        {(reports.local_lateness && reports.local_lateness[agentIndex]) && reports.local_lateness[agentIndex].length > 0
          && <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agents_lateness">
                    Lateness
              </Typography>
                </Box>
                <SimpleChart
                  dot={true}
                  multiline
                  colors={constants.colors}
                  field='time'
                  width={900}
                  height={300}
                  data={reports.local_lateness[agentIndex]}
                  ids={getTaskList(agentIndex)} // insert taskset here
                  type="monotone"
                  value='t_' />
              </Grid>
            </Paper>
          </Box>
        }
        {log[agentIndex] &&
          <Box p={2} className={classes.responsive}>
            <Paper>
              <Grid item xs={12} sm={6}>
                <Box p={2}>
                  <Typography variant="h6" id="agent_resp_time">
                    Taskset execution
              </Typography>
                </Box>
                <Box style={{ overflowX: 'auto', overflowY: 'hidden', width: 900, height: 'inherit' }}>
                  <GanttScatterChart
                    ratio={getMaxBudget(log[agentIndex])}
                    domain={Number(inputs.config.time)}
                    colors={constants.colors}
                    data={log[agentIndex]} />
                </Box>
              </Grid>
            </Paper>
          </Box>
        }
      </Grid>
    </>
  )
}

export default Analysis;
