import React from 'react';
import Button from '@material-ui/core/Button';
import Card from '@material-ui/core/Card';
import CardMedia from '@material-ui/core/CardMedia';
import CardContent from '@material-ui/core/CardContent';
import Typography from '@material-ui/core/Typography';
import { ThemeProvider } from "@material-ui/styles";
import theme from '../theme';

const createOverrides = ({ spacing, palette }) => ({
  MuiCard: {
    root: {
      '&.MuiPostCard--02': {
        borderRadius: spacing(2), // 16px
        transition: '0.3s',
        boxShadow: '0px 14px 80px rgba(34, 35, 58, 0.2)',
        position: 'relative',
        maxWidth: 800,
        // marginLeft: 'auto',
        overflow: 'initial',
        background: '#ffffff',
        display: 'flex',
        flexDirection: 'column',
        alignItems: 'center',
        padding: `${spacing(2)}px 0`,
        '&:hover': {
          transform: 'translateY(-3px)',
          boxShadow: '0 4px 20px 0 rgba(0,0,0,0.12)',
        },
        [theme.breakpoints.up('sm')]: {
          flexDirection: 'row',
          width: '95%',
        },
        '& .MuiCardMedia-root': {
          flexShrink: 0,
          position: 'relative',
          width: '80%',
          maxWidth: 256,
          marginTop: '-16%',
          paddingTop: '48%',
          boxShadow: '0px 14px 80px rgba(34, 35, 58, 0.2)',
          borderRadius: spacing(2), // 16px
          backgroundSize: 'contain',
          // backgroundImage: 'linear-gradient(147deg, #ffaac2 0%, #fd3838 74%)',
          backgroundColor: palette.common.white,
          overflow: 'hidden',
          [theme.breakpoints.up('sm')]: {
            width: '40%',
            marginTop: 0,
            marginLeft: '-8%',
            backgroundSize: 'cover',
          },
          '&:after': {
            content: '" "',
            position: 'absolute',
            top: 0,
            left: 0,
            width: '100%',
            height: '100%',
            // backgroundImage: 'linear-gradient(147deg, #ffaac2 0%, #fd3838 74%)',
            borderRadius: spacing(2), // 16
            opacity: 0.5,
          },
        },
        '& .MuiCardContent-root': {
          textAlign: 'center',
          padding: spacing(2),
          [theme.breakpoints.up('sm')]: {
            paddingLeft: spacing(3),
            textAlign: 'left',
          },
        },
        '& .MuiButton--readMore': {
          // backgroundImage: 'linear-gradient(147deg, #ff3366 0%, #ffaac2 74%)',
          backgroundColor: '#ff3366',
          boxShadow: '0px 14px 80px rgba(34, 35, 58, 0.2)',
          borderRadius: 100,
          paddingLeft: 24,
          paddingRight: 24,
          marginTop: 24,
          color: '#ffffff',
        },
      },
    },
  },
});

const PostCard = (props) => {
  const { bio } = props;
  return (
    <ThemeProvider
      theme={{
        ...theme,
        overrides: createOverrides(theme)
      }}
    >
      <Card className={'MuiPostCard--02'}>
        <CardMedia
          className={'MuiCardMedia-root'}
          image={bio.picture}
        />
        <CardContent className={'MuiCardContent-root'}>
          <Typography
            className={'MuiTypography--heading'}
            variant={'h6'}
            gutterBottom
          >
            {`${bio.name} ${bio.surname}`}
          </Typography>
          <Typography className={'MuiTypography--subheading'}>
            {bio.description}
          </Typography>
          <Button className={'MuiButton--readMore'} target="_blank" href={bio.linkedIn}>More</Button>
        </CardContent>
      </Card>
    </ThemeProvider>

  );
}

export default PostCard;