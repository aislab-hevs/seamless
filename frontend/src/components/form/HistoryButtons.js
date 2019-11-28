import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import {
  Button
} from '@material-ui/core';
import * as constants from '../../utils/constants';

const useStyles = makeStyles(theme => ({
  button: {
    margin: theme.spacing(1),
  },
}));

export default function HistoryButtons(props) {
  const { structure, setStructure, setStructureIndex, header, activeStep, structureIndex } = props
  const classes = useStyles();

  // perform a check before allowing to add tasks!
  const handleAdd = () => {
    let newIndex = Object.keys(structure).length;
    structure[newIndex] = {};
    setStructureIndex(newIndex);
  }

  const handleDelete = () => {
    if (structureIndex >= 0) {
      for (let i = structureIndex; i < Object.keys(structure).length - 1; i++) {
        structure[i] = structure[i + 1];
      }
      delete structure[Object.keys(structure).length - 1];
      setStructure(structure => ({ ...structure }))
    }
  }

  const getColor = index => {
    return header == 'TASKS'
      ? constants.colors[structure[index].agentExecutor % 10]
      : constants.colors[index % 10]
  }

  const getId = index => {
    switch (header) {
      case 'SERVERS':
        return structure[index].server_id || '-';
      case 'TASKS':
        return structure[index].id || '-';
      default: return index;
    }
  }

  return (
    <>
      <h3>{header}</h3>
      {Object.keys(structure).map((key, index) => {
        return <Button
          className={classes.button}
          key={`task-${key}`}
          variant="contained"
          onClick={() => setStructureIndex(index)}
          // style={{ backgroundColor: `${getColor(index)}`, color: '#ffffff' }}
          color='primary'
        >
          {/* {index + 1} */}
          {getId(index)}
        </Button>
      })}
      {activeStep !== 1 &&
        <Button
          className={classes.button}
          variant="contained"
          style={{ backgroundColor: constants.colors[2], color: '#ffffff' }}
          onClick={handleAdd}>
          Add
      </Button>}
      {activeStep !== 1 &&
        <Button
          disabled={Object.keys(structure).length === 1}
          className={classes.button}
          variant="contained"
          color="secondary"
          onClick={handleDelete}>
          Del
      </Button>}
    </>
  )
}