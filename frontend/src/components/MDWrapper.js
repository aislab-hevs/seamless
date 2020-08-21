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

import React, { useEffect, useState } from 'react';
import Typography from '../components/Typography';
import {
  Box,
  Grid,
  Hidden
} from '@material-ui/core';
import ContentNav from '../components/ContentNav';
import Markdown from '../components/Markdown';
import ScrollTop from '../components/ScrollTop';
import Fab from '@material-ui/core/Fab';
import KeyboardArrowUpIcon from '@material-ui/icons/KeyboardArrowUp';
import { makeStyles } from '@material-ui/styles'

const useStyles = makeStyles(theme => ({
  title: {
    borderLeft: `10px solid ${theme.palette.secondary.dark}`,
    paddingLeft: theme.spacing(2),
    [theme.breakpoints.down('md')]: {
      fontSize: '2.5rem',
    },
  },
}))

export default function MDWrapper(props) {
  const { file, title, sections } = props;
  const [markdown, setMarkdown] = useState('');
  const classes = useStyles();

  const fetchMd = async name => {
    const res = await fetch(name);
    const text = await res.text();
    setMarkdown(text);
  }

  useEffect(() => {
    // Load the md file on mounting
    fetchMd(file);
  }, []);

  return (
    <>
      <Grid container spacing={3}>
        <Grid item xs={12} sm={10}>
          <Box mr={3}>
            <Box pb={2} pt={4} id="back-to-top-anchor">
              <Typography variant='h2' className={classes.title}>
                {title}
              </Typography>
            </Box>
            <Markdown children={markdown} />
          </Box>
        </Grid>
        <Grid item sm={2}>
          <Hidden smDown>
            <Box pl={2}>
              {sections && <ContentNav sections={sections} />}
            </Box>
          </Hidden>
        </Grid>
      </Grid>
      <Hidden smUp>
        <ScrollTop selector='#back-to-top-anchor' {...props}>
          <Fab color="secondary" size="small" aria-label="scroll back to top">
            <KeyboardArrowUpIcon />
          </Fab>
        </ScrollTop>
      </Hidden>
    </>
  )
}