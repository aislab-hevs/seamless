import React from 'react';
import { makeStyles } from '@material-ui/core/styles';
import {
  Box,
  List,
  ListItem
} from '@material-ui/core';
import Typography from './Typography';

const useStyles = makeStyles(theme => ({
  nav: {
    position: "fixed",
    fontSize: 13,
    height: '82vh',
    overflowY: 'auto',
  },
  link: {
    textDecoration: 'none',
    textTransform: 'capitalize',
    // paddingLeft: theme.spacing(1),
    marginLeft: theme.spacing(-3),
    marginTop: theme.spacing(-1.2),
    fontSize: 11,
    cursor: 'pointer',
    "&:hover": {
      borderLeft: `4px solid ${theme.palette.secondary.dark}`,
      color: theme.palette.primary.dark,
      fontWeight: 'bold',
    },
    // "&:active": {
    //   borderLeft: `4px solid ${theme.palette.secondary.dark}`,
    //   color: theme.palette.secondary.dark
    // }
  },
  active: {
    borderLeft: `4px solid ${theme.palette.secondary.dark}`,
    color: theme.palette.secondary.dark
  }
}));

function ContentNav(props) {
  const { sections } = props;
  const classes = useStyles();
  // const [selected, setSelected] = React.useState(`#${sections[0].href}`);

  const handleClick = (event, selector) => {
    const anchor = (event.target.ownerDocument || document).querySelector(selector);

    if (anchor) {
      anchor.scrollIntoView({ behavior: 'smooth', block: 'start' });
    }
  };

  return (
    <Box pl={2} className={classes.nav}>
      <Typography variant='subtitle1' style={{ fontSize: 15 }}>
        <Box ml={-1} fontWeight="fontWeightBold">Contents</Box>
      </Typography>
      <List>
        {sections.map((section, index) => {
          let ref = `#${section.href}`;
          return (
            <ListItem key={index}>
              <div
                onClick={(e) => handleClick(e, ref)}
                style={{ paddingLeft: section.level * 6 }}
                className={classes.link}
                href={ref}>
                {section.name}
              </div>
            </ListItem>
          );
        }
        )}
      </List>
    </Box>
  )
}

export default ContentNav;