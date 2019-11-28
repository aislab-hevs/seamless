import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Paper from '@material-ui/core/Paper';
import * as constants from '../../utils/constants';

const useStyles = makeStyles(theme => ({
  root: {
    width: '100%',
    //  width: 785
  },
  paper: {
    // marginTop: theme.spacing(3),
    width: '100%',
    overflowX: 'auto',
    // marginBottom: theme.spacing(2),
  },
  table: {
    // width: 785, // static
  },
}));

export default function ServersTable(props) {
  const { servers } = props;
  const classes = useStyles();

  return (
    <div className={classes.root}>
      {servers.length > 0
        ? <Paper elevation={0} className={classes.paper}>
          <Table className={classes.table} size="small" aria-label="knowledge-table">
            <TableHead>
              <TableRow>
                <TableCell>Server Id</TableCell>
                <TableCell align="right">Agent</TableCell>
                <TableCell align="right">Bandwidth</TableCell>
                <TableCell align="right">Budget</TableCell>
                <TableCell align="right">Type</TableCell>
              </TableRow>
            </TableHead>
            <TableBody>
              {servers.map((server, index) => (
                <TableRow key={index}>
                  <TableCell>{server.server_id}</TableCell>
                  <TableCell align="right">{server.agent_id}</TableCell>
                  <TableCell align="right">{server.bandwidth}</TableCell>
                  <TableCell align="right">{server.budget}</TableCell>
                  <TableCell align="right">{constants.ServerType[server.type]}</TableCell>
                </TableRow>
              ))}
            </TableBody>
          </Table>
        </Paper>
        : 'No servers.'
      }
    </div>

  );
}
