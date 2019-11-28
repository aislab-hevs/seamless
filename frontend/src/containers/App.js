import React from 'react';
import Home from '../layouts/Home';
import Dashboard from '../layouts/Dashboard';
import withRoot from '../withRoot';
import SignIn from '../views/public/SignIn';
import SignUp from '../views/public/SignUp';
import ForgotPassword from '../views/public/ForgotPassword';
import PageNotFound from '../views/public/PageNotFound';

//routing with hookrouter
import { useRoutes } from 'hookrouter';

const routes = {
  '/': () => <Home />,
  '/dashboard*': () => <Dashboard />,
  '/signin': () => <SignIn />,
  '/signup': () => <SignUp />,
  '/recovery': () => <ForgotPassword />
}

function App() {
  const routeResult = useRoutes(routes);

  return routeResult || <PageNotFound />
}

export default withRoot(App);