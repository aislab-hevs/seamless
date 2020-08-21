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
import ReactMarkdown from 'markdown-to-jsx';
import { withStyles } from '@material-ui/core/styles';
import Box from '@material-ui/core/Box';
import Typography from '@material-ui/core/Typography';
import Link from '@material-ui/core/Link';
import clsx from 'clsx';

const styles = theme => ({
  listItem: {
    marginTop: theme.spacing(1),
  },
  header: {
    textTransform: 'uppercase',
    fontWeight: 'bold',
  },
  innerH1: {
    fontSize: 26,
  },
  innerH2: {
    fontSize: 22,
  },
  innerH3: {
    fontSize: 18,
  },
  innerH4: {
    fontSize: 14,
  },
});

const options = {
  overrides: {
    h2: { component: withStyles(styles)(({ classes, ...props }) => (<Box className={clsx(classes.innerH1, classes.header)}><Box pb={2} pt={11} mt={-8} {...props} /></Box>)), },
    h3: { component: withStyles(styles)(({ classes, ...props }) => (<Box className={clsx(classes.innerH2, classes.header)}><Box pb={2} pt={11} mt={-8} {...props} /></Box>)), },
    h4: { component: withStyles(styles)(({ classes, ...props }) => (<Box className={clsx(classes.innerH3, classes.header)}><Box pb={2} pt={11} mt={-8} {...props} /></Box>)), },
    h5: { component: withStyles(styles)(({ classes, ...props }) => (<Box className={clsx(classes.innerH4, classes.header)}><Box pb={2} pt={11} mt={-8} {...props} /></Box>)), },
    p: { component: withStyles(styles)(({ classes, ...props }) => (<Box className={classes.innerH4}><p {...props} /></Box>)) },
    a: { component: withStyles(styles)(({ classes, ...props }) => (<Link target="_blank" color='secondary' {...props} />)) },
    li: {
      component: withStyles(styles)(({ classes, ...props }) => (
        <li className={classes.listItem}>
          <Typography component="span" variant="body2" {...props} />
        </li>
      )),
    },
  },
};

function Markdown(props) {

  return <ReactMarkdown options={options} {...props} />;
}

export default Markdown;