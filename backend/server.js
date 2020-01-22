const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const knex = require('knex');
const sim = require('./controllers/sim');
const bcrypt = require('bcrypt-nodejs');

const register = require('./controllers/register');
const signin = require('./controllers/signin');
const profile = require('./controllers/profile');
const auth = require('./controllers/authorization');

const db = knex({
  client: 'pg',
  connection: process.env.POSTGRES_URI
});

const app = express();

app.use(bodyParser.json());
app.use(cors());

// protect the remaining endpoints (reports, simulation, ecc...)
app.get('/', (req, res) => res.send('Server up and running'));
app.post('/signin', signin.signinAuthentication(db, bcrypt));
app.post('/register', register.registerAuthentication(db, bcrypt));
app.get('/profile/:id', auth.requireAuth, profile.handleProfileGet(db))
app.post('/profile/:id/', auth.requireAuth, (req, res) => { profile.handleProfileUpdate(req, res, db) })
app.get('/simulation/reports/:user/:date', auth.requireAuth, (req, res) => sim.getReports(req, res));
app.get('/simulation/inputs/:user/:date', auth.requireAuth, (req, res) => sim.getInputs(req, res));
app.get('/simulation/config/:user/:date', auth.requireAuth, (req, res) => sim.getNedConfig(req, res));
app.get('/simulation/log/:user/:date', auth.requireAuth, (req, res) => sim.getLog(req, res));
app.get('/simulation/reports/:user', auth.requireAuth, (req, res) => sim.getSimulations(req, res));
app.post('/simulation', auth.requireAuth, (req, res) => sim.runSimulation(req, res));
app.post('/simulations/:user/delete', auth.requireAuth, (req, res) => sim.deleteSimulations(req, res));
app.get('/download/:user/:date', auth.requireAuth, (req, res) => sim.getSimulationFiles(req, res));

const PORT = process.env.SERVER_PORT || 4000;
app.listen(PORT, () => console.log(`Server listening on port ${PORT}`));