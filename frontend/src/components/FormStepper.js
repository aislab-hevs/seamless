import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import Stepper from '@material-ui/core/Stepper';
import Step from '@material-ui/core/Step';
import StepLabel from '@material-ui/core/StepLabel';
import Button from '@material-ui/core/Button';
import Hidden from '@material-ui/core/Hidden';
import Box from '@material-ui/core/Box';
import Typography from '@material-ui/core/Typography';

const useStyles = makeStyles(theme => ({
  root: {
    width: '90%',
  },
  button: {
    marginRight: theme.spacing(1),
  },
  instructions: {
    marginTop: theme.spacing(1),
    marginBottom: theme.spacing(1),
  },
}));

function getSteps() {
  return ['Simulation settings', 'Configure agents', 'Configure servers', 'Create tasksets', 'Configure needs'];
}

function getStepContent(step) {
  switch (step) {
    case 0:
      return 'Configure simulator...';
    case 1:
      return 'Add Agents';
    case 2:
      return 'Add Servers';
    case 3:
      return 'Add Tasks';
    case 4:
      return 'Add Needs';
    default:
      return 'Unknown step';
  }
}

export default function FormStepper(props) {
  const { activeStep, setActiveStep, submitData, setIgnored, skippable, nextable ,openSummary } = props;
  const classes = useStyles();
  const [skipped, setSkipped] = React.useState(new Set());
  const steps = getSteps();

  function isStepOptional(step) {
    return step === 1 || step === 2 || step === 4;
  }

  function isStepSkipped(step) {
    return skipped.has(step);
  }

  function handleNext() {
    let newSkipped = skipped;
    if (isStepSkipped(activeStep)) {
      newSkipped = new Set(newSkipped.values());
      newSkipped.delete(activeStep);
    }

    setActiveStep(prevActiveStep => prevActiveStep + 1);
    setSkipped(newSkipped);
  }

  function handleBack() {
    setActiveStep(prevActiveStep => prevActiveStep - 1);
  }

  function handleSkip() {
    if (!isStepOptional(activeStep)) {
      // You probably want to guard against something like this,
      // it should never occur unless someone's actively trying to break something.
      throw new Error("You can't skip a step that isn't optional.");
    }

    setActiveStep(prevActiveStep => prevActiveStep + 1);
    setSkipped(prevSkipped => {
      const newSkipped = new Set(prevSkipped.values());
      newSkipped.add(activeStep);
      setIgnored(newSkipped);
      return newSkipped;
    });
  }

  function handleReset() {
    setActiveStep(0);
    setIgnored(new Set());
  }

  return (
    <div className={classes.root}>
      <Box pt={2}>
        <Hidden smDown>
          <Stepper activeStep={activeStep}>
            {steps.map((label, index) => {
              const stepProps = {};
              const labelProps = {};
              if (isStepOptional(index)) {
                labelProps.optional = <Typography variant="caption">Optional</Typography>;
              }
              if (isStepSkipped(index)) {
                stepProps.completed = false;
              }
              return (
                <Step key={label} {...stepProps}>
                  <StepLabel {...labelProps}>{label}</StepLabel>
                </Step>
              );
            })}
          </Stepper>
        </Hidden>
        {activeStep === steps.length ? (
          <div>
            <Typography className={classes.instructions}>
              All steps completed - you&apos;re finished
            </Typography>
            <Button onClick={handleReset} className={classes.button}>
              Review
            </Button>
            <Button onClick={openSummary} className={classes.button}>
              Summary
            </Button>
            <Button variant="contained"
              color="secondary"
              onClick={submitData}
              className={classes.button}>
              Submit
            </Button>
          </div>
        ) : (
            <div>
              <Typography className={classes.instructions}>{getStepContent(activeStep)}</Typography>
              <div>
                <Button disabled={activeStep === 0} onClick={handleBack} className={classes.button}>
                  Back
              </Button>
                {isStepOptional(activeStep) && (
                  <Button
                    variant="contained"
                    color="primary"
                    onClick={handleSkip}
                    className={classes.button}
                    disabled={!skippable}
                  >
                    Skip
                </Button>
                )}

                <Button
                  variant="contained"
                  color="primary"
                  onClick={handleNext}
                  className={classes.button}
                  disabled={isStepOptional(activeStep) && !nextable}
                >
                  {/* {activeStep === steps.length - 1 ? 'Finish' : 'Next'} */}
                  {'Next'}
                </Button>
              </div>
            </div>
          )}
      </Box>
    </div>
  );
}
