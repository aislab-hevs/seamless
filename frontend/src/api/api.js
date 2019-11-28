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
    runSimulation,
    deleteSimulations
}