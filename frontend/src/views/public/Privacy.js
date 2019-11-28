import withRoot from '../../withRoot';
// --- Post bootstrap -----
import React, { useEffect, useState } from 'react';
import Container from '@material-ui/core/Container';
import Box from '@material-ui/core/Box';
import Markdown from '../../components/Markdown';
import Typography from '../../components/Typography';
import PublicBar from '../../components/PublicBar';
import privacyPath from './privacy.md';
import AppFooter from '../../components/AppFooter';

function Privacy() {
  const [privacy, setPrivacy] = useState('');

  useEffect(() => {
    // Update the document title using the browser API
    fetch(privacyPath)
      .then(res => res.text()).then(text => setPrivacy(text));
  });

  return (
    <React.Fragment>
      <PublicBar />
      <Container>
        <Box mt={7} mb={12}>
          <Typography variant="h3" gutterBottom marked="center" align="center">
            Privacy
          </Typography>
          <Markdown children={privacy}/>
        </Box>
      </Container>
      <AppFooter />
    </React.Fragment>
  );
}

export default withRoot(Privacy);
