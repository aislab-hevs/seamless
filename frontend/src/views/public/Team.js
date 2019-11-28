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
    description: 'Proident est do officia non veniam aliquip amet anim exercitation reprehenderit in eu dolore.',
    linkedIn: 'https://www.linkedin.com/in/giuseppe-albanese',
    picture: 'https://media.licdn.com/dms/image/C5603AQFhdoXAulFlUA/profile-displayphoto-shrink_200_200/0?e=1573084800&v=beta&t=F7EogEUT1KzjsYkYVud9qnBzvrRlHkue4bcH1rEulrA'
  },
  {
    name: 'Davide',
    surname: 'Calvaresi',
    description: 'Dolor reprehenderit labore excepteur duis irure laboris dolor nisi non quis tempor.',
    linkedIn: 'https://www.linkedin.com/in/davidecalvaresi',
    picture: 'https://media.licdn.com/dms/image/C4D03AQHQVUVPyh_fFg/profile-displayphoto-shrink_200_200/0?e=1573084800&v=beta&t=BmYTYoA2XguExRWwolXR_Y4UPDvrHOW-Rxh5dEeuTX8'
  },
  {
    name: 'Michael Ignaz',
    surname: 'Schumacher',
    description: 'Fugiat nulla labore cupidatat deserunt cupidatat occaecat deserunt nostrud.',
    linkedIn: 'https://www.linkedin.com/in/michael-ignaz-schumacher',
    picture: 'https://media.licdn.com/dms/image/C5103AQFYt_5GnOlMyQ/profile-displayphoto-shrink_200_200/0?e=1573084800&v=beta&t=dzS5l0_Y7ckEaHcvD_0tzfENnYz6DhXfln7Y9aQU4hY'
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
            Esse sunt consequat reprehenderit nisi tempor eu veniam officia culpa. Ipsum tempor do veniam officia. Enim sint nisi duis ex ad dolore culpa reprehenderit. Ut adipisicing ea ad reprehenderit duis laboris duis ut aute qui consequat labore officia. Excepteur deserunt sunt consequat minim nisi magna dolore incididunt aliqua enim sunt. Fugiat irure laboris veniam ea laboris.
           <br />
            <br />
            >Velit labore incididunt velit officia eiusmod proident aliquip dolore et. Cillum ipsum pariatur est sunt deserunt pariatur dolor eu commodo mollit ipsum quis. Est in tempor cillum esse incididunt ut cupidatat dolore incididunt nulla incididunt cillum. Deserunt labore est deserunt nisi labore veniam aute labore.
           <br />
            <br />
            Id quis laborum voluptate veniam ipsum aute adipisicing commodo excepteur irure deserunt. Et laborum sint nisi ex consectetur amet ullamco. Id laboris eiusmod ullamco dolore qui et duis ut.
           Esse sunt consequat reprehenderit nisi tempor eu veniam officia culpa. Ipsum tempor do veniam officia. Enim sint nisi duis ex ad dolore culpa reprehenderit. Ut adipisicing ea ad reprehenderit duis laboris duis ut aute qui consequat labore officia. Excepteur deserunt sunt consequat minim nisi magna dolore incididunt aliqua enim sunt. Fugiat irure laboris veniam ea laboris.
           <br />
            <br />
            Velit labore incididunt velit officia eiusmod proident aliquip dolore et. Cillum ipsum pariatur est sunt deserunt pariatur dolor eu commodo mollit ipsum quis. Est in tempor cillum esse incididunt ut cupidatat dolore incididunt nulla incididunt cillum. Deserunt labore est deserunt nisi labore veniam aute labore.
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