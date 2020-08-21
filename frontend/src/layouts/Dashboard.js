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
import DashBar from '../components/DashBar'
import ResponsiveDrawer from '../components/ResponsiveDrawer';
import History from '../views/private/History';
import Simulation from '../views/private/Simulation';
import Profile from '../views/private/Profile';
import Howto from '../views/public/Howto';
import Team from '../views/public/Team';
import Research from '../views/public/Research';
import About from '../views/public/About';
// import PageNotFound from '../views/public/PageNotFound';
import AppFooter from '../components/AppFooter';
import Grid from '@material-ui/core/Grid'
import Box from '@material-ui/core/Box'
import { makeStyles } from '@material-ui/styles'
//routing with hookrouter
import { useRoutes, navigate } from 'hookrouter';
import useSessionStorage from '../hooks/useSessionStorage';
import * as api from '../api/api';
import { Hidden } from '@material-ui/core';

const routes = {
  '/howto': () => (classes, props) => <Howto classes={classes} {...props} />,
  '/simulation': () => (classes, props) => <Simulation classes={classes} {...props} />,
  '/history*': () => (classes, props) => <History classes={classes} {...props} />,
  '/profile': () => (classes, props) => <Profile classes={classes} {...props} />,
  '/about': () => (classes, props) => <About classes={classes} {...props} />,
  '/team': () => (classes, props) => <Team classes={classes} {...props} />,
  '/research': () => (classes, props) => <Research classes={classes} {...props} />,
}

const useStyles = makeStyles(theme => ({
  root: {
    overflow: 'hidden',
    paddingTop: theme.spacing(2),
    paddingLeft: theme.spacing(4),
  },
  title: {
    borderLeft: `10px solid ${theme.palette.secondary.dark}`,
    paddingLeft: theme.spacing(2),
    [theme.breakpoints.down('md')]: {
      fontSize: '2.5rem',
    },
  },
  responsive: {
    [theme.breakpoints.up('lg')]: {
      marginLeft: theme.spacing(15),
    }
  }
}))

function Dashboard() {
  const routeResult = useRoutes(routes);
  const [mobileOpen, setMobileOpen] = useState(false);
  const classes = useStyles();

  const [token] = useSessionStorage('token');
  const [user, setUser] = useState('user');
  const [logged, setLogged] = useState(false);

  const loadUser = async (auth) => {
    if (auth && !logged) {
      const res = await api.signInWithToken(auth);
      if (res !== 'Unauthorized') {
        setUser(res);
        setLogged(true);
      }
      else navigate('/');
    } else {
      navigate('/');
    }
  }

  useEffect(() => {
    const abortController = new AbortController();
    loadUser(token);
    return () => { abortController.abort() }; //cleanup async calls
  }, [token])


  const handleDrawerToggle = () => {
    setMobileOpen(!mobileOpen);
  }

  return (
    <div className={classes.root}>
      <DashBar toggleDrawer={handleDrawerToggle} />
      <Box>
        <Grid container spacing={3}>
          <Grid item sm={1}>
            <ResponsiveDrawer toggleDrawer={handleDrawerToggle} mobileOpen={mobileOpen} />
          </Grid>
          {/* <Grid item lg={1} /> */}
          <Grid item xs={12} sm={11} md={10}>
            {logged &&
              <Box className={classes.responsive}>
                {routeResult
                  ? routeResult(classes, { user })
                  : navigate('/dashboard/howto')}
              </Box>}
          </Grid>
        </Grid>
        {/* <AppFooter /> */}
      </Box>
    </div>
  );
}

export default Dashboard;