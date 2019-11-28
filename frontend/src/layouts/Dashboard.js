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