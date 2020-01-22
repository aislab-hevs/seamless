const fs = require('fs')//.promises;
const constants = require('./constants');
const CONF_NAME = "net_config.ini";
const LOG_NAME = "ev_log";
const SIM_PATH = process.cwd() + '/simulator/simulations';

// seed-set -> modify to random seed!
// DON'T ADD SPACES NOR FORMAT TEXT! (because .ini file needs to be written like this)
const make_config = (config_json, agents_json) => {
    let config = `# Name = ${config_json.sim_name || '-'}
[General]
network = net_0
seed-set = ${new Date(config_json.date).getUTCMilliseconds()}
net_0.timestamp = "${config_json.date}"
net_0.user = "${config_json.user}"
*.n = ${config_json.agents_n}
*.DF.sched_type = ${config_json.DF_sched_type}
*.DF.quantum = ${config_json.DF_quantum !== undefined ? config_json.DF_quantum : -1} 
*.ag[*].neg_type = ${config_json.neg_type !== undefined ? config_json.neg_type : -1} 
*.DF.neg_type = ${config_json.neg_type !== undefined ? config_json.neg_type : -1}
*.ag[*].contractor_heuristic = ${config_json.contr_h !== undefined ? config_json.contr_h : -1}
*.DF.contractor_heuristic = ${config_json.contr_h !== undefined ? config_json.contr_h : -1}
*.ag[*].bidder_heuristic = ${config_json.bidder_h !== undefined ? config_json.bidder_h : -1}
*.DF.bidder_heuristic = ${config_json.bidder_h !== undefined ? config_json.bidder_h : -1}
*.DF.server_type = ${config_json.DF_server_type !== undefined ? config_json.DF_server_type : -1}
*.DF.server_budget = ${config_json.DF_server_budget !== undefined ? config_json.DF_server_budget : -1}
*.DF.server_period = ${config_json.DF_server_period !== undefined ? config_json.DF_server_period : -1}
*.DF.msg_server_mode = ${config_json.DF_msg_server_mode}
**.delay = uniform(${config_json.min_delay}ms, ${config_json.max_delay}ms)
sim-time-limit = ${config_json.time}s
cmdenv-express-mode = false
cmdenv-redirect-output = true
cmdenv-output-file = ./ev_log
# apply_for_all = ${config_json.apply_for_all}
`
    if (config_json.apply_for_all) {
        config = config.concat(`*.ag[*].sched_type = ${config_json.sched_type}
*.ag[*].server_type = ${config_json.server_type !== undefined ? config_json.server_type : -1}
*.ag[*].server_budget = ${config_json.server_budget !== undefined ? config_json.server_budget : -1}
*.ag[*].server_period = ${config_json.server_period !== undefined ? config_json.server_period : -1}
*.ag[*].msg_server_mode = ${config_json.msg_server_mode}
*.ag[*].quantum = ${config_json.quantum !== undefined ? config_json.quantum : -1}
`)
    } else {
        Object.keys(agents_json).forEach(id => {
            config = config.concat(
                `*.ag[${id}].sched_type = ${agents_json[id].sched_type}
*.ag[${id}].server_type = ${agents_json[id].server_type !== undefined ? agents_json[id].server_type : -1}
*.ag[${id}].server_budget = ${agents_json[id].server_budget !== undefined ? agents_json[id].server_budget : -1}
*.ag[${id}].server_period = ${agents_json[id].server_period !== undefined ? agents_json[id].server_period : -1}
*.ag[${id}].msg_server_mode = ${agents_json[id].msg_server_mode}
*.ag[${id}].quantum = ${agents_json[id].quantum !== undefined ? agents_json[id].quantum : -1}
`)
        })
    }
    return config
}

const checkDir = async dirpath => {
    try {
        await new Promise((resolve, reject) => {
            fs.mkdir(dirpath, { recursive: true }, (err) => {
                if (err) reject(err)
                resolve();
            })
        })
    } catch (err) {
        if (err.code !== 'EEXIST') throw err
    }
}

const writeConfig = async (dirpath, config_json, agents_json) => {
    try {
        let config = make_config(config_json, agents_json);
        await new Promise((resolve, reject) => {
            fs.writeFile(dirpath + CONF_NAME, config, (err) => {
                if (err) reject(err);
                resolve('Configuration file successfully written!');
            })
        }).then(msg => console.log(msg));
    } catch (err) {
        console.log(err);
    }
}

const writeInputs = async (dirpath, inputs_json) => {
    let input_dir = dirpath;
    try {
        let promises = [];
        Object.keys(inputs_json).forEach(async key => {
            promises.push(fs.writeFile(input_dir + key + ".json", JSON.stringify(inputs_json[key], null, 4), (err) => {
                if (err) return err;
            }));
        });
        await Promise.all(promises).then(console.log(`Input files successfully written!`));
    } catch (err) {
        console.log(err);
    }
}

const initializeFiles = async (config_json, inputs_json) => {
    let conf_path = `${SIM_PATH}/${config_json.user}/${config_json.date}/`;
    let input_path = conf_path + "inputs/"
    let inputs = parseInputs(inputs_json);
    try {
        await checkDir(conf_path);
        await checkDir(input_path);
        await writeConfig(conf_path, config_json, inputs.agents);
        await writeInputs(input_path, inputs);
    } catch (err) {
        console.log(err);
    }
}

// parse here and use in initialize files up
const parseInputs = inputs => {
    const { agents, knowledge, taskset, servers, needs } = inputs;
    return {
        agents: agents,
        knowledge: groupBy(knowledge, 'agentExecutor'), //TODO: change knowledge/taskset relation
        taskset: groupBy(taskset, 'agentExecutor'),
        servers: groupBy(servers, 'agent_id'),
        needs: groupBy(needs, 'agent_id')
    }
}

const groupBy = (struct, prop) => {
    let parsed = {};
    Object.keys(struct).forEach(index => {
        let ag = struct[index][prop];
        if (parsed[ag]) {
            parsed[ag].push(struct[index]);
        }
        else {
            parsed[ag] = [];
            parsed[ag].push(struct[index]);
        }
    });
    return parsed;
}

const toConfigObject = config_string => {
    return config_string.split('\n').reduce((acc, entry) => {
        let options = entry.split(' = ');
        acc[options[0]] = options[1];
        return acc;
    }, {});
}

const parseConfig = config => {
    let parsed = toConfigObject(config);
    let conf_obj = {
        'Date': new Date(parsed['net_0.timestamp'].split('"')[1]).toDateString(),
        'Number of agents': parsed["*.n"],
        'Scheduling algorithm': constants.SchedTypeEnum[+parsed["*.ag[*].sched_type"]],
        'Negotiation algorithm': constants.NegTypeEnum[+parsed["*.ag[*].neg_type"]],
        'Contractor heuristic': constants.ContractorPoliciesEnum[+parsed["*.ag[*].contractor_heuristic"]],
        'Bidder heuristic': constants.BidderPoliciesEnum[+parsed["*.ag[*].bidder_heuristic"]],
        'Message Server mode': parsed["*.ag[*].msg_server_mode"] === 'true' ? 'Enabled' : 'Disabled',
        'Message Server type': constants.ServerTypeEnum[+parsed["*.ag[*].server_type"]],
        'Channel delay': parsed["**.delay"],
        'Simulation time': parsed["sim-time-limit"],
    };
    if (parsed[`# apply_for_all`] === 'false') {
        for (let i = 0; i < parsed["*.n"]; i++) {
            conf_obj = {
                ...conf_obj,
                [`Agent ${i}`]: `${constants.SchedTypeEnum[+parsed[`*.ag[${i}].sched_type`]]}`,
            }
        }
    }
    return conf_obj;
}

const parseLocalRespTime = resp_time => {
    let parsed = {};
    if (resp_time) {
        for (let i = 0; i < resp_time.length; i++) {
            let times = [];
            if (resp_time[i] !== null) {
                for (let entry of resp_time[i]) {
                    times.push({
                        time: parseFloat(entry.finishTime.toFixed(2)),
                        [`t_${entry.taskId}`]: parseFloat(entry.responseTime.toFixed(2))
                    });
                }
            }

            parsed[i] = times.sort((a, b) => (a.time > b.time) ? 1 : ((b.time > a.time) ? -1 : 0));
        }
    }
    return parsed;
}

const parseLocalLateness = lateness => {
    let parsed = {};
    if (lateness) {
        for (let i = 0; i < lateness.length; i++) {
            let times = [];
            if (lateness[i]) {
                for (let entry of lateness[i]) {
                    times.push({
                        time: parseFloat(entry.finishTime.toFixed(2)),
                        [`t_${entry.id}`]: parseFloat(entry.lateness.toFixed(2))
                    });
                }
            }
            parsed[i] = times.sort((a, b) => (a.time > b.time) ? 1 : ((b.time > a.time) ? -1 : 0));
        }
        return parsed;
    }
    else return null
}

const parseLocalUtil = util => {
    if (util) {
        return util.map(entries => {
            if (entries !== null) return entries.map(entry => {
                return { ...entry, utilization: parseFloat(entry.utilization.toFixed(2)) }
            })
        })
    }
}

const parseLocalPotUtil = pot_util => {
    if (pot_util) {
        return pot_util.map(entries => {
            if (entries !== null) return entries.map(entry => {
                return { ...entry, [`potential utilization`]: parseFloat(entry.u_pot.toFixed(2)) }
            })
        })
    }
    return null;
}

const parseGlobalAccRatio = ratio => {
    if (ratio) {
        let parsed = [];
        for (let i = 0; i < ratio.length; i++) {
            let ar = (ratio[i].acc_ratio);
            parsed.push({ 'id': `ag_${i}`, 'acceptance': parseFloat(ar.toFixed(2)) })
        };
        return parsed;
    }
    return null;
}

const parseGlobalUtil = util => {
    if (util) {
        let parsed = [];
        for (let i = 0; i < util.length; i++) {
            if (util[i]) {
                for (let entry of util[i]) {
                    // let time = entry.time;
                    // if (parsed[time]) {
                    //     parsed[time] = { ...parsed[time], [`ag_${i}`]: parseFloat(entry.utilization.toFixed(2)) };
                    // } else {
                    parsed.push({ 'time': parseFloat(entry.time.toFixed(2)), [`ag_${i}`]: parseFloat(entry.utilization.toFixed(2)) });
                    // }
                }
            }
        }
        // let data = Object.keys(parsed).map(key => {
        //     return { 'time': parseFloat(Number(key).toFixed(2)), ...parsed[key] } // Check better rounding
        // });
        // return data.sort((a, b) => (a.time > b.time) ? 1 : ((b.time > a.time) ? -1 : 0));
        // return data.sort((a, b) => (a.time - b.time));
        return parsed.sort((a, b) => (a.time - b.time));
    }
    else return null
}

const parseGlobalRespTime = resp_time => { // could be useful...
    let parsed = {};
    for (let i = 0; i < resp_time.length; i++) {
        for (let entry of resp_time[i]) {
            let time = entry.finishTime;
            if (parsed[time]) {
                parsed[time] = { ...parsed[time], [`t_${entry.taskId}`]: parseFloat(entry.responseTime.toFixed(2)) };
            } else {
                parsed[time] = { [`t_${entry.taskId}`]: parseFloat(entry.responseTime.toFixed(2)) };
            }
        }
    }
    let data = Object.keys(parsed).map(key => {
        return { 'time': parseFloat(Number(key).toFixed(2)), ...parsed[key] } // Check better rounding
    });
    return data.sort((a, b) => (a.time > b.time) ? 1 : ((b.time > a.time) ? -1 : 0));;
}

const parseGlobalDMR = stats => {
    let parsed = [];
    for (let i = 0; i < stats.length; i++) {
        let dmr = (stats[i].ddlMissCount / stats[i].ddlCheckCount);
        parsed.push({ 'id': `ag_${i}`, 'dmr': parseFloat(dmr.toFixed(2)) })
    };
    return parsed;
}

const parseGlobalDdlMiss = ddl_miss => {
    if (ddl_miss) {
        let parsed = {};
        for (let entry of ddl_miss) {
            if (!parsed[entry.executor]) parsed[entry.executor] = {};
            else if (!parsed[entry.executor][entry.id]) parsed[entry.executor][entry.id] = 1;
            else parsed[entry.executor][entry.id]++;
        }
        return parsed;
        // return Object.keys(parsed).map(key => {
        //     return { 'id': `t_${key}`, ddl_miss: parsed[key] }
        // });
    } else return null
}

const parseLocalDMR = (ddl_miss, ddl_checks) => {
    let ddl_miss_parsed = null;
    if (ddl_miss) {
        ddl_miss_parsed = parseGlobalDdlMiss(ddl_miss);
    }
    if (ddl_checks && ddl_miss_parsed) {
        let parsed = {};
        for (let [agent, values] of Object.entries(ddl_miss_parsed)) {
            for (let [task, miss] of Object.entries(values)) {
                if (!parsed[agent]) parsed[agent] = [];
                let check = ddl_checks[agent][task];
                parsed[agent].push({ 'id': `t_${task}`, dmr: Math.round((miss / check) * 100) / 100, miss: miss, checks: check });
            }
        }
        return parsed;
    } else return null
}


const parseLog = log => {
    const lines = log.split('\n');
    let parsed = {};
    let processors = {};
    for (let line of lines) {
        if (line.includes('INFO')) {
            let time = Number(line.substring(line.indexOf('t: ') + 2, line.lastIndexOf(',')));
            let ag = line.substring(line.indexOf('tskEx: ag[') + 10, line.lastIndexOf(']'));
            let task = line.substring(line.indexOf('tskId:[') + 7, line.lastIndexOf('] tskDm'));
            let is_server = line.includes('SERVER');
            let entry;
            let srv_id

            if (is_server) {
                srv_id = line.split(' ')[3];
                entry = `S ${srv_id}`
            } else {
                entry = `T ${task}`
            }

            if (!processors[ag]) {
                processors[ag] = {}
            }

            if (line.includes('ACTIVATED')) {
                let budget = null;

                if (!processors[ag][`${entry}`]) {
                    processors[ag][`${entry}`] = { cpu_start: 0, cpu_end: 0 }
                }

                if (is_server) {
                    // srv_id = line.substring(line.indexOf('SERVER ') + 7, line.lastIndexOf(' ACTIVATED'));
                    budget = Number(line.substring(line.indexOf('budget: ') + 8, line.length));
                    processors[ag][`${entry}`][`budget`] = budget;
                }

                processors[ag][`${entry}`].cpu_start = time;

                if (!parsed[ag]) parsed[ag] = { [`${entry}`]: [] };
                else if (!parsed[ag][`${entry}`]) parsed[ag][`${entry}`] = [];

                for (let i = processors[ag][`${entry}`].cpu_end; i < processors[ag][`${entry}`].cpu_start; i++) {
                    parsed[ag][`${entry}`].push({ time: i, index: 1, value: 0, task: task })
                }
            }

            else if (line.includes('COMPLETED') || line.includes('PREEMPTED') || line.includes('EXPIRED')) {
                let budget = null;

                if (is_server) {
                    // srv_id = line.split(' ')[3];
                    budget = processors[ag][`${entry}`][`budget`];
                }

                processors[ag][`${entry}`].cpu_end = time;

                if (!parsed[ag]) parsed[ag] = { [`${entry}`]: [] };
                else if (!parsed[ag][`${entry}`]) parsed[ag][`${entry}`] = [];

                let i;

                for (i = processors[ag][`${entry}`].cpu_start; i < processors[ag][`${entry}`].cpu_end; i++) {
                    // the case below is needed to cover a DSS replenish in the middle of a task execution!
                    if (processors[ag][`${entry}`][`replenish_${i}`] && i != processors[ag][`${entry}`].cpu_start) {
                        let amount = processors[ag][`${entry}`][`replenish_${i}`];
                        parsed[ag][`${entry}`].push({ time: i, index: 1, value: 500, budget: budget && (budget + amount) - 1, task: task })
                    }
                    else parsed[ag][`${entry}`].push({ time: i, index: 1, value: 500, budget: budget && budget--, task: task })
                }

                if (is_server) {
                    if (line.includes('PREEMPTED') || line.includes('COMPLETED')) parsed[ag][`${entry}`].push({ time: i, index: 1, value: 0, budget: budget && budget--, task: task })
                    if (line.includes('EXPIRED')) parsed[ag][`${entry}`].push({ time: i, index: 1, value: 0, budget: 0, task: task })
                }
            }
            else if (line.includes('REPLENISH')) {
                let budget = Number(line.substring(line.indexOf('budget: ') + 8, line.length));
                let amount = Number(line.substring(line.indexOf('amount: ') + 8, line.indexOf(' budget')));
                processors[ag][`${entry}`][`replenish_${time}`] = amount;
                parsed[ag][`${entry}`].push({ time: time, index: 1, value: 0, budget: budget, task: task })
            }
        }
    }
    for (let ag in parsed) {
        for (let task in parsed[ag]) {
            parsed[ag][task].sort((a, b) => a.time - b.time || a.budget - b.budget);
        }
    }
    return parsed;
}

const mergeUtil = (util, pot_util) => {
    if (util && pot_util) {
        let u_arr = parseLocalUtil(util);
        let pot_u_arr = parseLocalPotUtil(pot_util)
        let merged = u_arr.map((arr, ag) => {
            return pot_u_arr[ag] !== undefined
                ? arr.concat(pot_u_arr[ag])
                : arr;
        })
        return merged.map(array => array && array.sort((a, b) => a.time - b.time));
    }
    return null;
}

const parseReports = reports => {
    return {
        resp_per_task: reports.resp_per_task,
        util: parseLocalUtil(reports.util),
        stats: reports.stats,
        local_resp_time: parseLocalRespTime(reports.resp_time),
        local_lateness: parseLocalLateness(reports.lateness),
        local_pot_util: parseLocalPotUtil(reports.pot_util),
        local_dmr: parseLocalDMR(reports.ddl_miss, reports.ddl_checks),
        global_acc_ratio: parseGlobalAccRatio(reports.acc_ratio),
        global_resp_time: reports.resp_time,
        global_util: parseGlobalUtil(reports.util),
        global_dmr: parseGlobalDMR(reports.stats),
        // global_ddl_miss: parseGlobalDdlMiss(reports.ddl_miss),
        merged_util: mergeUtil(reports.util, reports.pot_util)
    }
}

module.exports = {
    SIM_PATH,
    LOG_NAME,
    CONF_NAME,
    initializeFiles,
    toConfigObject,
    parseConfig,
    parseInputs,
    parseReports,
    parseLog
}