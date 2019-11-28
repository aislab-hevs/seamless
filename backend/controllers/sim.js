const fs = require('fs');
const parser = require('../utils/parser');
const { exec } = require('child_process'); //NB see 'spawn' to have more control on the execution of commands
const AGENT_PATH = process.cwd() + '/simulator/agent_gprt/';
const REPORTS = ["ddl_miss.json", "lateness.json", "resp_per_task.json", "resp_time.json", "stats.json", "util.json", "pot_util.json", "acc_ratio.json"];
const INPUTS = ["agents.json", "knowledge.json", "needs.json", "servers.json", "taskset.json"];
const CONFIG = "net_config.ini";

const runSimulation = async (req, res) => {
    try {
        const { config, inputs } = req.body;
        await parser.initializeFiles(config, inputs);
        let config_path = `../simulations/${config.user}/${config.date}/${parser.CONF_NAME}`
        // need to be in the same folder of the sim to run properly -> cd
        await new Promise((resolve, reject) => {
            exec(`cd ${AGENT_PATH} && ./agent_gprt -u Cmdenv -f ${config_path}`, (error, stdout, stderr) => {
                if (error !== null) {
                    reject(error);
                }
                resolve(console.log(stdout))
            });
        });
        //write awk log
        const log_path = `${parser.SIM_PATH}/${config.user}/${config.date}`
        await new Promise((resolve, reject) => {
            exec(`awk '/ACTIVATED|COMPLETED|PREEMPTED|EXPIRED|REPLENISH/' ${log_path}/${parser.LOG_NAME} \
             >  ${log_path}/awk_log`, (error, stdout, stderr) => {
                if (error !== null) {
                    reject(error);
                }
                resolve(console.log('awk_log successfully written!'));
            });
        });
        return res.status(200).json(`Simulation completed!`)
    } catch (error) {
        console.log(error);
        return res.status(500).json(`Simulation failed - ` + error);
    }
}

const getReports = async (req, res) => {
    const { user, date } = req.params;
    try {
        let reports = {};
        for (let file of REPORTS) {
            let name = [file.split('.')[0]];
            reports[name] = await new Promise((resolve, reject) => {
                fs.readFile(`${parser.SIM_PATH}/${user}/${date}/reports/${file}`,
                    (err, entry) => {
                        if (err) {
                            if (err.code === 'ENOENT') {
                                console.error(`${file} does not exist`);
                                reject(err);
                            };
                            reject(err);
                        }
                        else resolve(JSON.parse(entry));
                    }
                )
            });
        }
        const parsed = parser.parseReports(reports);
        res.status(200).json(parsed);
    } catch (err) {
        console.log(err);
        res.status(404).json("File not found");
    }
}

const getInputs = async (req, res) => {
    const { user, date } = req.params;
    try {
        let inputs = {};
        for (let file of INPUTS) {
            let name = [file.split('.')[0]];
            inputs[name] = await new Promise((resolve, reject) => {
                fs.readFile(`${parser.SIM_PATH}/${user}/${date}/inputs/${file}`,
                    (err, entry) => {
                        if (err) {
                            if (err.code === 'ENOENT') {
                                console.error(`${file} does not exist`);
                                reject(err);
                            };
                            reject(err);
                        }
                        else resolve(JSON.parse(entry));
                    }
                )
            });
        }
        const config_string = await new Promise((resolve, reject) => {
            fs.readFile(`${parser.SIM_PATH}/${user}/${date}/${CONFIG}`,
                (err, file) => {
                    if (err) reject(err);
                    resolve(String(file));
                }
            )
        });
        const conf_obj = parser.toConfigObject(config_string);
        inputs['config'] = conf_obj;
        res.status(200).json(inputs);
    } catch (err) {
        console.log(err);
        res.status(404).json("File not found");
    }
}

const getSimulations = (req, res) => {
    const { user } = req.params;
    try {
        exec(`ls ${parser.SIM_PATH}/${user}`, (error, stdout, stderr) => {
            if (error !== null) {
                console.log(error);
            }
            res.status(200).json(stdout.split('\n').filter(el => el !== ''));
        });
    } catch (err) {
        console.log(err);
        res.status(404).json("File not found");
    }
}

const getNedConfig = async (req, res) => {
    const { user, date } = req.params;
    try {
        let config = await new Promise((resolve, reject) => {
            fs.readFile(`${parser.SIM_PATH}/${user}/${date}/${parser.CONF_NAME}`,
                (err, data) => {
                    if (err) {
                        if (err.code === 'ENOENT') {
                            console.error(`${file} does not exist`);
                            reject(err);
                        };
                        reject(err);
                    }
                    else resolve(data);
                }
            )
        });
        res.status(200).send(parser.parseConfig(String(config)));
    } catch (err) {
        console.log(err);
        res.status(404).json("File not found");
    }
}

const getLog = async (req, res) => {
    const { user, date } = req.params;
    try {
        let log = await new Promise((resolve, reject) => {
            fs.readFile(`${parser.SIM_PATH}/${user}/${date}/awk_log`,
                (err, data) => {
                    if (err) {
                        if (err.code === 'ENOENT') {
                            console.error(`${file} does not exist`);
                            reject(err);
                        };
                        reject(err);
                    }
                    else resolve(data);
                }
            )
        });
        res.status(200).send(parser.parseLog(String(log)));
    } catch (err) {
        console.log(err);
        res.status(404).json("File not found");
    }
}

const deleteSimulations = async (req, res) => {
    const { user } = req.params;
    const { simulations } = req.body
    try {
        for (let date of simulations) {
            exec(`rm -rf ${parser.SIM_PATH}/${user}/${date}`, (error, stdout, stderr) => {
                if (error !== null) {
                    console.log(error);
                }
            });
        }
        let sim = simulations.length > 1 ? 'Simulations' : 'Simulation';
        res.status(200).json(`${sim} deleted`);
    } catch (err) {
        console.log(err);
        res.status(404).json("Simulation not found");
    }
}

module.exports = {
    runSimulation,
    getReports,
    getInputs,
    getSimulations,
    getNedConfig,
    getLog,
    deleteSimulations
}