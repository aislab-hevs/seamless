import React from 'react'
import Typography from '../../components/Typography';
import {
  Box
} from '@material-ui/core';

function Research(props) {
  return (
    <>
      <Box pb={2} pt={4}>
        <Typography variant='h2' className={props.classes.title}>
          Research
        </Typography>
      </Box>
    </>
  )
}

export default Research;