import React from 'react';
import PropTypes from 'prop-types';
import clsx from 'clsx';
import { withStyles } from '@material-ui/core/styles';
import AppBar from './AppBar';
import Toolbar, { styles as toolbarStyles } from './Toolbar';
import MenuIcon from '@material-ui/icons/Menu';
import { navigate } from 'hookrouter';
import {
  Hidden,
  Link,
  Menu,
  MenuItem,
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
    fontSize: 15,
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
  }
});

function PublicBar(props) {
  const [anchorEl, setAnchorEl] = React.useState(null);

  function handleClick(event) {
    setAnchorEl(event.currentTarget);
  }

  function handleClose() {
    setAnchorEl(null);
  }

  const { classes } = props;

  return (
    <div>
      <AppBar position="fixed">
        <Toolbar className={classes.toolbar}>
          <div className={classes.left} />
          <img src={require("../assets/seamless-logo.svg")} alt='logo' className={classes.logo}/>
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
            <Hidden xsDown>
              <Link
                color="inherit"
                variant="h6"
                underline="none"
                className={classes.rightLink}
                href="/signin"
              >
                {'Sign In'}
              </Link>
              <Link
                variant="h6"
                underline="none"
                className={clsx(classes.rightLink, classes.linkSecondary)}
                href="/signup"
              >
                {'Sign Up'}
              </Link>
            </Hidden>
            <Hidden smUp>
              <IconButton
                aria-label="more"
                aria-controls="long-menu"
                aria-haspopup="true"
                onClick={handleClick}
              >
                <MenuIcon color='secondary' />
              </IconButton>
              <Menu
                id="simple-menu"
                anchorEl={anchorEl}
                keepMounted
                open={Boolean(anchorEl)}
                onClose={handleClose}
              >
                <MenuItem onClick={() => { navigate('/signin') }}>Sign in</MenuItem>
                <MenuItem onClick={() => { navigate('/signup') }}>Sign up</MenuItem>

              </Menu>
            </Hidden>
          </div>
        </Toolbar>
      </AppBar>
      <div className={classes.placeholder} />
    </div>
  );
}

PublicBar.propTypes = {
  classes: PropTypes.object.isRequired,
};

export default withStyles(styles)(PublicBar);
