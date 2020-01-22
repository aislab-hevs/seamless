import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import Paper from '@material-ui/core/Paper';
import Tooltip from '@material-ui/core/Tooltip';

const useStyles = makeStyles(theme => ({
  root: {
    width: '100%',
    // width: 785,
  },
  paper: {
    // marginTop: theme.spacing(3),
    width: '100%',
    overflowX: 'auto',
    // marginBottom: theme.spacing(2),
  },
  table: {
    // minWidth: 650,
  },
}));

export default function KnowledgeTable(props) {
  const { knowledge } = props;
  const classes = useStyles();

  return (
    <div className={classes.root}>
      <Paper elevation={0} className={classes.paper}>
        <Table className={classes.table} size="small" aria-label="knowledge-table">
          <TableHead>
            <TableRow>
              <Tooltip title='Task id' placement='top'><TableCell>Id</TableCell></Tooltip>
              <Tooltip title='Executor' placement='top'><TableCell align="right">Ex</TableCell></Tooltip>
              <Tooltip title='Demander' placement='top'><TableCell align="right">Dm</TableCell></Tooltip>
              <Tooltip title='Computation time' placement='top'><TableCell align="right">C</TableCell></Tooltip>
              <Tooltip title='Residual computation time' placement='top'><TableCell align="right">CRes</TableCell></Tooltip>
              <Tooltip title='Release time' placement='top'><TableCell align="right">R</TableCell></Tooltip>
              <Tooltip title='Period' placement='top'><TableCell align="right">T</TableCell></Tooltip>
              <Tooltip title='Relative Deadline' placement='top'><TableCell align="right">D</TableCell></Tooltip>
              <Tooltip title='Number of executions' placement='top'><TableCell align="right">n</TableCell></Tooltip>
              <Tooltip title='First activation time' placement='top'><TableCell align="right">f.R</TableCell></Tooltip>
              <Tooltip title='Last activation time' placement='top'><TableCell align="right">l.R</TableCell></Tooltip>
              <Tooltip title='Server' placement='top'><TableCell align="right">S</TableCell></Tooltip>
              <Tooltip title='Public task' placement='top'><TableCell align="right">Pub</TableCell></Tooltip>
              <Tooltip title='Active in taskset' placement='top'><TableCell align="right">Act</TableCell></Tooltip>
            </TableRow>
          </TableHead>
          <TableBody>
            {knowledge.sort((a, b) => a.id - b.id).map((task, index) => (
              <TableRow key={index}>
                <TableCell align="right">{task.id}</TableCell>
                <TableCell align="right">{task.agentExecutor === -1 ? 'All' : task.agentExecutor}</TableCell>
                <TableCell align="right">{task.agentDemander === -1 ? 'All' : task.agentDemander}</TableCell>
                <TableCell align="right">{task.computationTime}</TableCell>
                <TableCell align="right">{task.residualComputationTime}</TableCell>
                <TableCell align="right">{task.arrivalTime}</TableCell>
                <TableCell align="right">{task.period}</TableCell>
                <TableCell align="right">{task.relativeDeadline}</TableCell>
                <TableCell align="right">{task.n_exec}</TableCell>
                <TableCell align="right">{task.firstActivationTime}</TableCell>
                <TableCell align="right">{task.lastActivationTime}</TableCell>
                <TableCell align="right">{task.server}</TableCell>
                <TableCell align="right">{task.isPublic ? '✓' : '✗'}</TableCell>
                <TableCell align="right">{task.inTaskset ? '✓' : '✗'}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </Paper>
    </div>
  );
}
