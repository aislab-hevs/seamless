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
import Analysis from './Analysis';
import EnhancedTable from '../../components/tables/EnhancedTable';
import Typography from '../../components/Typography';
import {
  Grid,
  Box
} from '@material-ui/core';
import Loading from '../../components/Loading';
import { useRoutes, navigate } from 'hookrouter';
import useSessionStorage from '../../hooks/useSessionStorage';
import * as api from '../../api/api';

const routes = {
  '/analysis/:user/:run': ({ user, run }) => <Analysis user={user} run={run} />,
}

function History(props) {
  const [loading, setLoading] = useState(true);
  const routeResults = useRoutes(routes);
  const [runs, setRuns] = useState([]);
  const [token] = useSessionStorage('token');
  const { user } = props

  const createData = (number, year, month, month_name, day, hour, name, ref) => {
    return { number, year, month, month_name, day, hour, name, ref };
  }

  const parseDate = isoDate => {
    let date = new Date(isoDate);
    let year = date.getFullYear();
    let month = date.getMonth();
    let month_name = date.toLocaleString('EN', { month: 'long' });
    let day = date.getDate();
    let hour = date.getHours();
    return { year, month, month_name, day, hour };
  }

  const fetchSimulations = async (name, auth) => {
    const res = await api.getSimulations(name, auth);
    if (res) {
      let runs = res.map((run, index) => {
        const { year, month, month_name, day, hour } = parseDate(run.date);
        return createData(index + 1, year, month, month_name, day, hour, run.name, run.date);
      });
      setRuns(runs);
      setLoading(false);
    }
  };

  const deleteSelection = async (selection) => {
    setLoading(true);
    await api.deleteSimulations(user.email, selection, token);
    setTimeout(() => { setRuns({}) }, 1000); // to force re-render
  }

  useEffect(() => {
    const abortController = new AbortController();
    if (token) fetchSimulations(user.email, token);
    return () => { abortController.abort() }; //cleanup async calls
  }, [token, runs.length])

  return (
    <Box pr={4}>
      <>
        <Box pb={2} pt={4}>
          <Typography variant='h2' className={props.classes.title}>
            History
        </Typography>
        </Box>
      </>
      {loading
        ? <Loading />
        :
        <>
          {routeResults ||
            <Grid item xs={12} sm={11}>
              <EnhancedTable user={user.email} rows={runs} navigate={navigate} deleteSelection={deleteSelection} />
            </Grid>
          }
        </>
      }
    </Box>
  );
}

export default History;