import React from 'react'
import Typography from '../../components/Typography';
import {
  Box,
  Grid
} from '@material-ui/core';
import PostCard from '../../components/PostCard';

const people = [
  {
    name: 'Giuseppe',
    surname: 'Albanese',
    description: 'Software Engineer.',
    linkedIn: 'https://www.linkedin.com/in/giuseppe-albanese',
    picture: 'https://www.hevs.ch/media/image/3/thumb_1_1/473a5493.jpg'
  },
  {
    name: 'Davide',
    surname: 'Calvaresi',
    description: 'Senior Researcher.',
    linkedIn: 'https://www.linkedin.com/in/davidecalvaresi',
    picture: 'https://www.hevs.ch/media/image/3/thumb_1_1/473a5495.jpg'
  },
  {
    name: 'Michael Ignaz',
    surname: 'Schumacher',
    description: 'Full Professor and director of the AISLAB research group.',
    linkedIn: 'https://www.linkedin.com/in/michael-ignaz-schumacher',
    picture: 'https://www.hevs.ch/media/image/1/thumb_1_1/044_img_1248.jpg'
  },
]

function Team(props) {
  return (
    <>
      <Box pb={2} pt={4} pr={4}>
        <Typography variant='h2' className={props.classes.title}>
          Team
        </Typography>
        <Box pb={4} pt={4}>
          <Box pb={4}>
            <Typography variant='h4'>
              Aislab
        </Typography>
          </Box>
          <Typography variant='body1'>
            The Applied Intelligent Agents Lab (AISLab) is applying Intelligent Agent and Multiagent techniques to healthcare. Its methodology is bottom-up, thus starting from real requirements in close collaborations with healthcare professionals and actors, trying to find the best available techniques to solve them. The lab activities cover mainly the following areas:
           <br />
           <br />
            - Intelligent agents for Personalized Medicine <br />
            - Health sensors monitoring and decision support <br />
            - Semantic data representation, interoperability and blockchain technologies for health data exchange
           <br />
           <br />
           For those areas, the lab develops solutions in integrating Artificial Intelligence with modern software technologies with a focus on mobile, Web and Semantic Web technologies.
          </Typography>
        </Box>
        <Box>
          <Box pb={8} pt={4}>
            <Typography variant='h4'>
              People
        </Typography>
          </Box>
          <Grid container spacing={8}>
            {people.map((bio, index) =>
              <Grid item xs={12} sm={4} key={index}>
                <PostCard bio={bio} />
              </Grid>)}
          </Grid>
        </Box>
      </Box>
    </>
  )
}

export default Team;
