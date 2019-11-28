import React from 'react';
import PropTypes from 'prop-types';
import { withStyles } from '@material-ui/core/styles';
import AppBar from './AppBar';
import Toolbar, { styles as toolbarStyles } from './Toolbar';
import ExitToAppIcon from '@material-ui/icons/ExitToApp';
import { navigate } from 'hookrouter';
import MenuIcon from '@material-ui/icons/Menu';
import {
  Hidden,
  Link,
  IconButton
} from '@material-ui/core'

const styles = theme => ({
  title: {
    fontSize: 15,
  },
  placeholder: toolbarStyles(theme).root,
  toolbar: {
    justifyContent: 'space-between',
  },
  left: {
    // flex: 1,
  },
  leftLinkActive: {
    color: theme.palette.common.white,
  },
  right: {
    flex: 1,
    display: 'flex',
    justifyContent: 'flex-end',
  },
  rightLink: {
    fontSize: 16,
    color: theme.palette.common.white,
    marginLeft: theme.spacing(3),
  },
  linkSecondary: {
    color: theme.palette.secondary.main,
  },
  logo: {
    alt: 'logo',
    width: 30,
    height: 30,
    paddingRight: 5
  },
  appBar: {
    zIndex: theme.zIndex.drawer + 1,
  },
});

function DashBar(props) {
  const { classes } = props;

  const logout = () => {
    window.sessionStorage.clear();
    navigate('/');
  }

  return (
    <div>
      <AppBar position="fixed" className={classes.appBar} id='dashbar'>
        <Toolbar className={classes.toolbar}>
          <div className={classes.left} />
          <img src={require("../assets/seamless-logo.svg")} alt='logo' className={classes.logo} />
          <Link
            variant="h6"
            underline="none"
            color="inherit"
            className={classes.title}
            href="/"
          >
            {'Seamless'}
          </Link>
          <div className={classes.right}>
            <Hidden mdDown>
              <IconButton
                aria-label="more"
                aria-controls="long-menu"
                aria-haspopup="true"
                onClick={logout}
              >
                <ExitToAppIcon color='secondary' />
              </IconButton>
            </Hidden>
            <Hidden lgUp>
              <IconButton
                aria-label="more"
                aria-controls="long-menu"
                aria-haspopup="true"
                onClick={props.toggleDrawer}
              >
                <MenuIcon color='secondary' />
              </IconButton>
            </Hidden>
          </div>
        </Toolbar>
      </AppBar>
      <div className={classes.placeholder} />
    </div>
  );
}

DashBar.propTypes = {
  classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(DashBar);
