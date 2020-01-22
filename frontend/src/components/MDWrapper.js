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