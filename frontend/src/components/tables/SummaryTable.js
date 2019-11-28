import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableRow from '@material-ui/core/TableRow';
import Typography from '../Typography';

const useStyles = makeStyles(theme => ({
  table: {
    minWidth: 600,
    maxWidth: '90%',
  },
}));

export default function SummaryTable(props) {
  const { data } = props;
  const classes = useStyles();

  return (data
    ?
    (<Table className={classes.table}>
      <TableBody>
        {Object.keys(data).map(key => (
          <TableRow key={key}>
            <TableCell component="th" scope="row">
              <Typography variant='h5'>{key}</Typography>
            </TableCell>
            <TableCell align="right">
              <Typography variant='h6'>{data[key]}</Typography>
            </TableCell>
          </TableRow>
        ))}
      </TableBody>
    </Table>)
    : <Typography variant='h6'>Nothing here</Typography>
  );
}