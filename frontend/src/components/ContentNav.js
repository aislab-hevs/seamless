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
import {
  Box,
  List,
  ListItem
} from '@material-ui/core';
import Typography from './Typography';

const useStyles = makeStyles(theme => ({
  nav: {
    position: "fixed",
    fontSize: 13,
    height: '82vh',
    overflowY: 'auto',
  },
  link: {
    textDecoration: 'none',
    textTransform: 'capitalize',
    // paddingLeft: theme.spacing(1),
    marginLeft: theme.spacing(-3),
    marginTop: theme.spacing(-1.2),
    fontSize: 11,
    cursor: 'pointer',
    "&:hover": {
      borderLeft: `4px solid ${theme.palette.secondary.dark}`,
      color: theme.palette.primary.dark,
      fontWeight: 'bold',
    },
    // "&:active": {
    //   borderLeft: `4px solid ${theme.palette.secondary.dark}`,
    //   color: theme.palette.secondary.dark
    // }
  },
  active: {
    borderLeft: `4px solid ${theme.palette.secondary.dark}`,
    color: theme.palette.secondary.dark
  }
}));

function ContentNav(props) {
  const { sections } = props;
  const classes = useStyles();
  // const [selected, setSelected] = React.useState(`#${sections[0].href}`);

  const handleClick = (event, selector) => {
    const anchor = (event.target.ownerDocument || document).querySelector(selector);

    if (anchor) {
      anchor.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }
  };

  return (
    <Box pl={2} className={classes.nav}>
      <Typography variant='subtitle1' style={{ fontSize: 15 }}>
        <Box ml={-1} fontWeight="fontWeightBold">Contents</Box>
      </Typography>
      <List>
        {sections.map((section, index) => {
          let ref = `#${section.href}`;
          return (
            <ListItem key={index}>
              <div
                onClick={(e) => handleClick(e, ref)}
                style={{ paddingLeft: section.level * 6 }}
                className={classes.link}
                href={ref}>
                {section.name}
              </div>
            </ListItem>
          );
        }
        )}
      </List>
    </Box>
  )
}

export default ContentNav;