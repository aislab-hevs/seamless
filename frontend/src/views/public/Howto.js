import React from 'react'
import {
  Box,
  Grid,
  Hidden,
} from '@material-ui/core'
import Typography from '../../components/Typography';
import ContentNav from '../../components/ContentNav';
import ScrollTop from '../../components/ScrollTop';
import Fab from '@material-ui/core/Fab';
import KeyboardArrowUpIcon from '@material-ui/icons/KeyboardArrowUp';

const sections = [
  { name: 'Summary', href: 'Summary', level: 1 },
  { name: 'Simulations', href: 'Simulations', level: 1 },
  { name: 'Tasksets', href: 'Tasksets', level: 1 },
  { name: 'Needs', href: 'Needs', level: 1 }
]

function Howto(props) {
  return (
    <React.Fragment>
      <Grid container spacing={3}>
        <Grid item xs={12} sm={10}>
          <Box pr={4}>
            <Box pb={2} pt={4} id='back-to-top-anchor'>
              <Typography variant='h2' className={props.classes.title}>
                Guide
        </Typography>
            </Box>
            <Box pb={2} pt={11} mt={-8} id='Summary'>
              <Typography variant='h6'>
                Summary
        </Typography>
            </Box>
            <Box>
              Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.
      </Box>
            <Box pb={2} pt={11} mt={-8} id='Simulations'>
              <Typography variant='h6'>
                Simulations
        </Typography>
            </Box>
            <Box>
              Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.
      </Box>
            <Box pb={2} pt={11} mt={-8} id='Tasksets'>
              <Typography variant='h6'>
                Tasksets
        </Typography>
            </Box>
            <Box>
              Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.
      </Box>
            <Box pb={2} pt={11} mt={-8} id='Needs'>
              <Typography variant='h6'>
                Needs
        </Typography>
            </Box>
            <Box>
              Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.Labore cillum ut ad voluptate irure duis ullamco. Sint occaecat excepteur
               ea sunt cupidatat nulla. Dolor voluptate ullamco mollit proident cillum quis in.
               Dolore deserunt velit cupidatat fugiat Lorem minim est eu reprehenderit adipisicing
               do exercitation mollit. Anim anim excepteur aliqua ea. Irure proident commodo eu sint
               deserunt eu non.
      </Box>
          </Box>
        </Grid>
        <Grid item sm={2}>
          <Hidden smDown>
            <Box pl={2}>
              <ContentNav sections={sections} />
            </Box>
          </Hidden>
        </Grid>
      </Grid>
      <Hidden smUp>
        <ScrollTop selector='#back-to-top-anchor' {...props}>
          <Fab color="secondary" size="small" aria-label="scroll back to top">
            <KeyboardArrowUpIcon />
          </Fab>
        </ScrollTop>
      </Hidden>
    </React.Fragment>
  )
}

export default Howto;