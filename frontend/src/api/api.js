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

const PROTOCOL = process.env.REACT_APP_PROTOCOL;
// const SOCKET_PROTOCOL = process.env.REACT_APP_SOCKET_PROTOCOL;
const SERVER_HOST = process.env.REACT_APP_SERVER_HOST || "localhost";
const SERVER_PORT = process.env.REACT_APP_SERVER_PORT || 5000;

const URL = `${PROTOCOL}://${SERVER_HOST}:${SERVER_PORT}`;

const signIn = async (email, password) => {
    try {
        let res = await fetch(`${URL}/signin`, {
            method: 'post',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                email: email,
                password: password,
            })
        });
        return res = await res.json();
    } catch (error) {
        console.log(error)
    }
}

const getProfileById = async (id, token) => {
    try {
        let res = await fetch(`${URL}/profile/${id}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        return await res.json();

    } catch (error) {
        console.log(error)
    }
}

const signInWithToken = async (token) => {
    try {
        let res = await fetch(`${URL}/signin`, {
            method: 'post',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        res = await res.json();
        return await getProfileById(res.id, token);

    } catch (error) {
        console.log(error)
    }
}

const signUp = async (name, surname, email, password) => {
    try {
        let res = await fetch(`${URL}/register`, {
            method: 'post',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
                name: name,
                surname: surname,
                email: email,
                password: password,
            })
        });
        return res = await res.json();
    } catch (error) {
        console.log(error)
    }
}

const getSimulations = async (user, token) => {
    try {
        let res = await fetch(`${URL}/simulation/reports/${user}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        return res = await res.json();

    } catch (error) {
        console.log(error)
    }
}

const getReports = async (user, date, token) => {
    try {
        let res = await fetch(`${URL}/simulation/reports/${user}/${date}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        return res = await res.json();

    } catch (error) {
        console.log(error)
    }
}

const getInputs = async (user, date, token) => {
    try {
        let res = await fetch(`${URL}/simulation/inputs/${user}/${date}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        return res = await res.json();

    } catch (error) {
        console.log(error)
    }
}

const getConfig = async (user, date, token) => {
    try {
        let res = await fetch(`${URL}/simulation/config/${user}/${date}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        return res = await res.json();

    } catch (error) {
        console.log(error)
    }
}

const getLog = async (user, date, token) => {
    try {
        let res = await fetch(`${URL}/simulation/log/${user}/${date}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
        });
        return res = await res.json();

    } catch (error) {
        console.log(error)
    }
}

const getSimulationFiles = async (user, date, token) => {
    try {
        let res = await fetch(`${URL}/download/${user}/${date}`, {
            method: 'get',
            headers: {
                'Content-Type': 'application/gzip',
                'Authorization': token
            },
        });
        return res = await res.blob();

    } catch (error) {
        console.log(error)
    }
}

const runSimulation = async (config, inputs, token) => {
    try {
        let res = await fetch(`${URL}/simulation`, {
            method: 'post',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
            body: JSON.stringify({
                config: config,
                inputs: inputs,
            })
        });
        return res = await res.json();

    } catch (error) {
        console.log(error)
    }
}

const deleteSimulations = async (user, simulations, token) => {
    try {
        let res = await fetch(`${URL}/simulations/${user}/delete`, {
            method: 'post',
            headers: {
                'Content-Type': 'application/json',
                'Authorization': token
            },
            body: JSON.stringify({
                simulations: simulations
            })
        });
        return res = await res.json();
    } catch (error) {
        console.log(error)
    }
}

export {
    signIn,
    signInWithToken,
    getProfileById,
    signUp,
    getSimulations,
    getReports,
    getInputs,
    getConfig,
    getLog,
    getSimulationFiles,
    runSimulation,
    deleteSimulations
}