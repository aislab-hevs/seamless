import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import { useTheme } from '@material-ui/core/styles';
import useMediaQuery from '@material-ui/core/useMediaQuery';
import Button from '@material-ui/core/Button';
import Dialog from '@material-ui/core/Dialog';
import DialogActions from '@material-ui/core/DialogActions';
import DialogContent from '@material-ui/core/DialogContent';
import DialogTitle from '@material-ui/core/DialogTitle';

const useStyles = makeStyles(theme => ({
  root: {
    width: '100%',
  },
  heading: {
    fontSize: theme.typography.pxToRem(15),
    fontWeight: theme.typography.fontWeightBold,
  },
  '@global': {
    '.MuiExpansionPanelDetails-root': {
      padding: '5px 24px'
    },
    '.MuiExpansionPanelSummary-root': {
      display: 'grid',
      gridAutoFlow: 'column',
      alignItems: 'center',
      justifyContent: 'start',
      overflowY: 'hidden'
    }
  },
}));


export default function DialogWrapper(props) {
  const { title, open, onClose } = props;
  const theme = useTheme();
  const classes = useStyles();
  const fullScreen = useMediaQuery(theme.breakpoints.down('sm'));

  return (
    <div className={classes.root}>
      <Dialog
        scroll='paper'
        fullScreen={fullScreen}
        maxWidth={props.maxWidth}
        open={open}
        onClose={onClose}
        aria-labelledby="responsive-dialog-title"
      >
        <DialogTitle id="responsive-dialog-title">{title}</DialogTitle>
        <DialogContent>
          {props.children}
        </DialogContent>
        <DialogActions>
          <Button variant='contained' onClick={onClose} color="primary" size='small'>
            Close
          </Button>
          {props.onView &&
            <Button disabled={!props.ready} variant='contained' onClick={props.onView} color="secondary" size='small'>
              View
          </Button>
          }
        </DialogActions>
      </Dialog>
    </div>
  );
}
