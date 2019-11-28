import withRoot from '../withRoot';
// --- Post bootstrap -----
import React from 'react';
import PublicBar from '../components/PublicBar';
import ProductHero from '../views/public/ProductHero';
import ProductValues from '../views/public/ProductValues';
import ProductHowItWorks from '../views/public/ProductHowItWorks';
import ProductSmokingHero from '../views/public/ProductSmokingHero';
import AppFooter from '../components/AppFooter';

function Home() {
  // const routeResult = useRoutes(routes);

  return (
    <React.Fragment>
      <PublicBar />
      <ProductHero />
      <ProductValues />
      <ProductHowItWorks />
      <ProductSmokingHero />
      <AppFooter />
    </React.Fragment>
  );
}

export default withRoot(Home);
