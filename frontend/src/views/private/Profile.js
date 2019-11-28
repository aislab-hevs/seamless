import React from 'react';
import SummaryTable from '../../components/tables/SummaryTable';
import Typography from '../../components/Typography';
import {
  Box
} from '@material-ui/core';

function Profile(props) {
  const { user } = props;

  return (
    <>
      <Box pb={2} pt={4} style={{ overfloX: 'auto' }}>
        <Typography variant='h2' className={props.classes.title}>
          Profile
        </Typography>
      </Box>
      <Box pb={2} pt={4}>
        <Typography component='li'><span>Name:</span> {user.name}</Typography>
        <Typography component='li'><span>Surname:</span> {user.surname}</Typography>
        <Typography component='li'><span>Email:</span> {user.email}</Typography>
        <Typography component='li'><span>Joined:</span> {new Date(user.joined).toLocaleString()}</Typography>
      </Box>
    </>
  )
}

export default Profile;