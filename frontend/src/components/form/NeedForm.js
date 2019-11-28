import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import {
  TextField,
  FormLabel,
  FormGroup,
  FormControl,
  InputLabel,
  Select,
  MenuItem,
  Grid
} from '@material-ui/core';
import * as constants from '../../utils/constants';

const useStyles = makeStyles(theme => ({
  spaced: {
    margin: theme.spacing(1),
    maxWidth: 240,
  }
}));

const ITEM_HEIGHT = 48;
const ITEM_PADDING_TOP = 8;
const MenuProps = {
  PaperProps: {
    style: {
      maxHeight: ITEM_HEIGHT * 4.5 + ITEM_PADDING_TOP,
      width: 250,
    },
  },
};

export default function NeedForm(props) {
  const { getAgentsMenuItems, setNeeds, needs, needIndex, tasks, neg_type, use_neg, error } = props;
  const classes = useStyles();

  // WARNING! Dark magic here
  const handleChange = index => event => {
    event.persist();
    if (!needs[index]) needs[index] = {};
    setNeeds(needs => ({
      ...needs, // keep old needs (whole)...
      [index]: {
        ...needs[index], // keep already set properties...
        [event.target.name]: event.target.value // update new values
      }
    }));
  };

  const getPublicTasks = (needIndex) => {
    const pub_tasks = [];
    Object.keys(tasks).forEach(index => {
      if (tasks[index].isPublic && tasks[index].agentExecutor !== needs[needIndex].agent_id) pub_tasks.push(tasks[index].id)
    });
    return [...new Set(pub_tasks)]; // delete duplicates
  }

  return (
    <div className={classes.root}>
      <FormLabel component="legend">Need Configuration</FormLabel>
      <Grid container spacing={4}>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            <FormControl className={classes.spaced}>
              <InputLabel error={error[`Need ${needIndex + 1} Agent Id`]} htmlFor='agent_id'>Agent Id</InputLabel>
              <Select
                disabled={!use_neg}
                value={(needs[needIndex] && needs[needIndex].agent_id) || ''}
                error={error[`Need ${needIndex + 1} Agent Id`]}
                onChange={handleChange(needIndex)}
                inputProps={{
                  name: `agent_id`,
                  id: `agent_id`,
                }}
                MenuProps={MenuProps}
              >
                <MenuItem value={-1}>All</MenuItem>
                {getAgentsMenuItems()}
              </Select>
            </FormControl>
            <TextField
              id="releaseTime"
              name="releaseTime"
              className={classes.spaced}
              label="Release time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              disabled={!use_neg}
              value={(needs[needIndex] && needs[needIndex].releaseTime) || ''}
              error={error[`Need ${needIndex + 1} Release time`] || (needs[needIndex] && needs[needIndex].releaseTime < 0)}
              helperText={(needs[needIndex] && needs[needIndex].releaseTime < 0) ? 'Must be greater than 0' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="neededTimeout"
              name="neededTimeout"
              className={classes.spaced}
              label="Bidding window"
              placeholder="0"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              disabled={!use_neg}
              value={(needs[needIndex] && needs[needIndex].neededTimeout) || ''}
              error={error[`Need ${needIndex + 1} Bidding window`] || (needs[needIndex] && needs[needIndex].neededTimeout < 0)}
              helperText={(needs[needIndex] && needs[needIndex].neededTimeout < 0) ? 'Must be greater than or equal to 0' : "seconds"}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 0,
                }
              }}
            />
            <TextField
              id="neededTaskRelease"
              name="neededTaskRelease"
              className={classes.spaced}
              label="Needed Task Release Time"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              disabled={!use_neg}
              value={(needs[needIndex] && needs[needIndex].neededTaskRelease) || ''}
              error={error[`Need ${needIndex + 1} Needed Task Release Time`] || (needs[needIndex] && (Number(needs[needIndex].neededTaskRelease) < Number(needs[needIndex].releaseTime)))}
              helperText={(needs[needIndex] && (Number(needs[needIndex].neededTaskRelease) < Number(needs[needIndex].releaseTime))) ? 'Must be greater than release time' : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="neededTaskDeadline"
              name="neededTaskDeadline"
              className={classes.spaced}
              label="Needed Task Deadline"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              disabled={!use_neg}
              value={(needs[needIndex] && needs[needIndex].neededTaskDeadline) || ''}
              error={error[`Need ${needIndex + 1} Needed Task Deadline`]}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
          </FormGroup>
        </Grid>
        <Grid item xs={12} sm={6}>
          <FormGroup>
            <TextField
              id="neededTaskNExec"
              name="neededTaskNExec"
              className={classes.spaced}
              label="Needed Task Executions"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              disabled={!use_neg}
              value={(needs[needIndex] && needs[needIndex].neededTaskNExec) || ''}
              error={error[`Need ${needIndex + 1} Needed Task Executions`]}
              helperText={'Leave -1 to have indefinite executions'}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="neededTaskTMin"
              name="neededTaskTMin"
              className={classes.spaced}
              label="Minimum Task Period"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              value={(needs[needIndex] && needs[needIndex].neededTaskTMin) || ''}
              disabled={!use_neg || (neg_type !== constants.NegTypeEnum['RBN'] && neg_type !== constants.NegTypeEnum['RBN_PLUS'])}
              error={(error[`Need ${needIndex + 1} Minimum Task Period`]) || 
              ((neg_type === constants.NegTypeEnum['RBN'] || neg_type === constants.NegTypeEnum['RBN_PLUS']) &&
                needs[needIndex].neededTaskTMin < 1)}
              helperText={(neg_type === constants.NegTypeEnum['RBN'] || (neg_type === constants.NegTypeEnum['RBN_PLUS']) &&
                Number(needs[needIndex].neededTaskTMin) < 1)
                ? 'Must be greater than 0'
                : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <TextField
              id="neededTaskTMax"
              name="neededTaskTMax"
              className={classes.spaced}
              label="Maximum Task Period"
              placeholder="1"
              margin="normal"
              fullWidth
              onChange={handleChange(needIndex)}
              value={(needs[needIndex] && needs[needIndex].neededTaskTMax) || ''}
              disabled={!use_neg || (neg_type !== constants.NegTypeEnum['RBN'] && neg_type !== constants.NegTypeEnum['RBN_PLUS'])}
              error={(error[`Need ${needIndex + 1} Maximum Task Period`]) ||
                ((neg_type === constants.NegTypeEnum['RBN'] || (neg_type === constants.NegTypeEnum['RBN_PLUS'])) &&
                (needs[needIndex] && (Number(needs[needIndex].neededTaskTMax) < Number(needs[needIndex].neededTaskTMin))))
              }
              helperText={(needs[needIndex] && (Number(needs[needIndex].neededTaskTMax) < Number(needs[needIndex].neededTaskTMin)))
                ? 'Must be greater than minimum period'
                : undefined}
              InputProps={{
                inputProps: {
                  type: 'number',
                  min: 1,
                  max: 100,
                }
              }}
            />
            <FormControl className={classes.spaced}>
              <InputLabel error={error[`Need ${needIndex + 1} Needed Tasks`]} htmlFor='neededTasks'>Needed Tasks</InputLabel>
              <Select
                multiple
                disabled={!use_neg}
                value={(needs[needIndex] && needs[needIndex].neededTasks) || []}
                error={error[`Need ${needIndex + 1} Needed Tasks`]}
                onChange={handleChange(needIndex)}
                inputProps={{
                  name: `neededTasks`,
                  id: `neededTasks`,
                }}
                MenuProps={MenuProps}
              >
                {getPublicTasks(needIndex).map((task, index) => {
                  return <MenuItem
                    key={index}
                    value={task}>{task}
                  </MenuItem>
                })}
              </Select>
            </FormControl>
          </FormGroup>
        </Grid>
      </Grid>
    </div>
  )
}