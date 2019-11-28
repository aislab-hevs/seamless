import React from 'react';
import {
  Divider,
  Drawer,
  Hidden,
  List,
  ListItem,
  ListItemText,
  ListSubheader,
  Box,
  Button,
} from '@material-ui/core';
import ExitToAppIcon from '@material-ui/icons/ExitToApp';
import DirectionsIcon from '@material-ui/icons/Directions';
import ComputerIcon from '@material-ui/icons/Computer';
import HistoryIcon from '@material-ui/icons/History';
import PersonIcon from '@material-ui/icons/Person';
import AdbIcon from '@material-ui/icons/Adb';
import GroupIcon from '@material-ui/icons/Group';
import DescriptionIcon from '@material-ui/icons/Description';
import { makeStyles, useTheme } from '@material-ui/core/styles';
import clsx from 'clsx';
import { navigate } from 'hookrouter';

const drawerWidth = 240;

const useStyles = makeStyles(theme => ({
  root: {
    display: 'flex',
  },
  drawer: {
    [theme.breakpoints.up('sm')]: {
      width: drawerWidth,
      flexShrink: 0,
    },
  },
  menuButton: {
    marginRight: theme.spacing(2),
    [theme.breakpoints.up('sm')]: {
      display: 'none',
    },
  },
  toolbar: theme.mixins.toolbar,
  drawerPaper: {
    width: drawerWidth,
    top: theme.spacing(8),
    paddingBottom: theme.spacing(8)
  },
  content: {
    flexGrow: 1,
    padding: theme.spacing(3),
  },
  selected: {
    "& div": { // apply to child div
      color: theme.palette.secondary.dark
    }
  },
  icon: {
    color: theme.palette.icon,
    width: 24,
    height: 24,
    display: 'flex',
    alignItems: 'center',
    marginRight: theme.spacing(1)
  },
  button: {
    color: theme.palette.primary.dark,
    padding: '10px 8px',
    justifyContent: 'flex-start',
    textTransform: 'none',
    letterSpacing: 0,
    width: '100%',
    fontWeight: theme.typography.fontWeightMedium,
    "&:active, &:hover": {
      backgroundColor: theme.palette.secondary.light,
      color: theme.palette.secondary.dark
    },
  },
}));

const pages = [
  {
    name: 'How to',
    path: '/dashboard/howto',
    icon: <DirectionsIcon />,
  },
  {
    name: 'Simulation',
    path: '/dashboard/simulation',
    icon: <ComputerIcon />,
  },
  {
    name: 'History',
    path: '/dashboard/history',
    icon: <HistoryIcon />,
  },
  {
    name: 'Profile',
    path: '/dashboard/profile',
    icon: <PersonIcon />,
  },
  {
    name: 'Maxim-GPRT',
    path: '/dashboard/about',
    icon: <AdbIcon />,
  },
  {
    name: 'Team',
    path: '/dashboard/team',
    icon: <GroupIcon />,
  },
  {
    name: 'Research',
    path: '/dashboard/research',
    icon: <DescriptionIcon />,
  }
];

function ResponsiveDrawer(props) {
  const { container } = props;
  const classes = useStyles();
  const theme = useTheme();

  const logout = () => {
    window.sessionStorage.clear();
    navigate('/');
  }

  const drawer = (
    <Box p={2}>
      <List>
        {pages.map((page, index) => {
          return (
            <React.Fragment key={index}>
              {page.name === 'Maxim-GPRT' && <ListSubheader aria-labelledby="about-subheader">
                About
              </ListSubheader>}
              <ListItem>
                <Button
                  className={clsx(
                    classes.button,
                    (window.location.pathname.includes(page.path) && classes.selected))} // highlight matching path (TODO: maybe not optimal way)
                  href={page.path}
                >
                  <div className={classes.icon}>{page.icon}</div>
                  <ListItemText primary={page.name} />
                </Button>
              </ListItem>
            </React.Fragment>
          );
        })
        }
        <Hidden lgUp>
          <Divider />
          <ListItem>
            <Button className={classes.button} onClick={logout}>
              <div className={classes.icon}><ExitToAppIcon /></div>
              <ListItemText primary={`Logout`} />
            </Button>
          </ListItem>
        </Hidden>
      </List>
    </Box>
  );

  return (
    <>
      {/* The implementation can be swapped with js to avoid SEO duplication of links. */}
      <Hidden mdUp implementation="css">
        <Drawer
          container={container}
          variant="temporary"
          anchor={theme.direction === 'rtl' ? 'right' : 'left'}
          open={props.mobileOpen}
          onClose={props.toggleDrawer}
          classes={{
            paper: classes.drawerPaper,
          }}
          ModalProps={{
            keepMounted: true, // Better open performance on mobile.
          }}
        >
          {drawer}
        </Drawer>
      </Hidden>
      <Hidden mdDown implementation="css">
        <div className={classes.root}>
          <nav className={classes.drawer} aria-label="nav links">
            <Drawer
              classes={{
                paper: classes.drawerPaper,
              }}
              variant="permanent"
              open
            >
              {drawer}
            </Drawer>
          </nav>
        </div>
      </Hidden>
    </>
  );
}

export default ResponsiveDrawer;