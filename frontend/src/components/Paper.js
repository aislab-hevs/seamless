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
import clsx from 'clsx';
import PropTypes from 'prop-types';
import MuiPaper from '@material-ui/core/Paper';
import { capitalize } from '@material-ui/core/utils';
import { withStyles } from '@material-ui/core/styles';

const styles = theme => ({
  backgroundLight: {
    backgroundColor: theme.palette.secondary.light,
  },
  backgroundMain: {
    backgroundColor: theme.palette.secondary.main,
  },
  backgroundDark: {
    backgroundColor: theme.palette.secondary.dark,
  },
  padding: {
    padding: theme.spacing(1),
  },
});

function Paper(props) {
  const { background = 'light', classes, className, padding = false, ...other } = props;
  return (
    <MuiPaper
      elevation={0}
      square
      className={clsx(
        classes[`background${capitalize(background)}`],
        {
          [classes.padding]: padding,
        },
        className,
      )}
      {...other}
    />
  );
}

Paper.propTypes = {
  background: PropTypes.oneOf(['light', 'main', 'dark']),
  classes: PropTypes.object.isRequired,
  className: PropTypes.string,
  padding: PropTypes.bool,
};

export default withStyles(styles)(Paper);
