import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import CircularProgress from '@material-ui/core/CircularProgress';
import Container from '@material-ui/core/Container';

const useStyles = makeStyles(theme => ({
    center: {
        textAlign: "center",
        paddingTop: theme.spacing(10),
    },
    progress: {
        margin: theme.spacing(2),
    },
}));

export default function Loading() {
    const classes = useStyles();

    return (
        <Container className={classes.center}>
            <CircularProgress className={classes.progress} color="secondary" />
        </Container>
    );
}
