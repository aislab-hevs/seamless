import React from 'react';
import {
  Box,
  Container
} from '@material-ui/core';

export default function PageNotFound() {
  return (
    <Container maxWidth='xs'>
      <Box pt={10} style={{ textAlign: 'center' }} fontSize={150} color='text.secondary'>
        404
        <Box style={{ textAlign: 'center' }} fontSize={50} color='text.secondary'>
          Move along fella!
        </Box>
      </Box>

    </Container>
  )
}