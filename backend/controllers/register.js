const auth = require('./authorization');

// Switched order to make it work with FOREIGN KEY in login table (email)
const handleRegister = (db, bcrypt, req, res) => {
    const { email, name, surname, password } = req.body;
    if (!email || !name || !surname || !password) {
        return Promise.reject('incorrect form submission');;
    }
    const hash = bcrypt.hashSync(password);
    //create transaction to keep consistency!
    return db.transaction(trx => {
        trx.insert({
            name: name,
            surname: surname,
            email: email,
            joined: new Date()
        })
            .into('users')
            .returning('*')
            .then(users => {
                let user = users[0];
                return trx('login')
                    .returning('*')
                    .insert({
                        email: user.email,
                        hash: hash,
                    })
                    .then(() => {
                        return user
                    })
            })
            .then(trx.commit)
            .catch(trx.rollback)
    })
        .catch(err => Promise.reject('user data invalid', err));
}

// NOTE: Do something similar to signinAuthentication when first registering
const registerAuthentication = (db, bcrypt) => (req, res) => {
    handleRegister(db, bcrypt, req, res)
        .then(data => {
            console.log(data);
            return data.id && data.email ? auth.createSessions(data) : Promise.reject(data)
        })
        .then(session => res.json(session))
        .catch(err => res.status(400).json(err));
}


module.exports = {
    handleRegister,
    registerAuthentication
};