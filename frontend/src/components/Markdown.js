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