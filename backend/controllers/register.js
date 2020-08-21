/*
 * Copyright (c) 2020, HES-SO Valais-Wallis (https://www.hevs.ch)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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