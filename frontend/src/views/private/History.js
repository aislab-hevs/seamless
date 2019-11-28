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

  const createData = (name, year, month, month_name, day, hour, ref) => {
    return { name, year, month, month_name, day, hour, ref };
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
        const { year, month, month_name, day, hour } = parseDate(run);
        return createData(index + 1, year, month, month_name, day, hour, run);
      });
      setRuns(runs);
      setLoading(false);
    }
  };

  const deleteSelection = async (selection) => {
    setLoading(true);
    await api.deleteSimulations(user.name, selection, token);
    await fetchSimulations(user.name, token);
  }

  useEffect(() => {
    const abortController = new AbortController();
    if (token) fetchSimulations(user.name, token);
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
              <EnhancedTable user={user.name} rows={runs} navigate={navigate} deleteSelection={deleteSelection} />
            </Grid>
          }
        </>
      }
    </Box>
  );
}

export default History;