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
