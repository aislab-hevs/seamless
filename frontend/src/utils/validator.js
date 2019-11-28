const checkConfigForm = (config, error, setError) => {
    error['Number of agents'] = Number.isNaN(Number(config.agents_n)) || Number(config.agents_n) < 0;
    error['Minimum channel delay'] = Number.isNaN(Number(config.min_delay)) || Number(config.min_delay) < 0;
    error['Maximum channel delay'] = Number.isNaN(Number(config.max_delay)) || Number(config.max_delay) < Number(config.min_delay);
    error['Simulation Time'] = Number.isNaN(Number(config.time)) || Number(config.time) < 0 || config.time === undefined;
    error['DF Scheduling Algorithm'] = config.DF_sched_type === undefined;
    if (config.DF_sched_type === 1) {
        error['DF quantum'] = config.DF_quantum === '' || Number(config.DF_quantum) < 0
    }
    if (config.DF_msg_server_mode) {
        error['DF Message server type'] = config.DF_server_type === undefined;
    }
    if (config.apply_for_all) {
        error['Scheduling Algorithm'] = config.sched_type === undefined;
        if (config.sched_type === 1) {
            error['Quantum'] = config.quantum === '' || Number(config.quantum) < 0
        }
        if (config.msg_server_mode) {
            error['Message server type'] = config.server_type === undefined
        }
    }
    if (config.use_neg) {
        error['Negotiation Protocol'] = config.neg_type === undefined;
        error['Contractor Heuristic'] = config.contr_h === undefined;
        error['Bidder Heuristic'] = config.bidder_h === undefined;
        // error['Bidding window'] = Number.isNaN(Number(config.agents_n)) || Number(config.neg_timeout) < 0;
    }
    setError(error);
}

const checkAgentsForm = (agents, error, setError, ignored) => {
    for (let [id, agent] of Object.entries(agents)) {
        error[`Agent ${Number(id) + 1} Scheduling Algorithm`] = ignored ? false : agent.sched_type === undefined;
        if (agent.msg_server_mode) {
            error[`Agent ${Number(id) + 1} Message server type`] = ignored ? false : agent.server_type === undefined;
        }
        if (agent.sched_type === 1) {
            error[`Agent ${Number(id) + 1} Quantum`] = ignored ? false : agent.quantum === '' || Number(agent.quantum) < 0
        }
    }
    setError(error);
}

const checkServersForm = (servers, error, setError, ignored) => {
    for (let [id, server] of Object.entries(servers)) {
        error[`Server ${Number(id) + 1} Agent Id`] = ignored ? false : server.agent_id === undefined;
        error[`Server ${Number(id) + 1} Id`] = ignored ? false : server.server_id === undefined;
        error[`Server ${Number(id) + 1} Bandwidth`] = ignored ? false : server.bandwidth === undefined || server.bandwidth === '' || Number(server.bandwidth) > 1
        error[`Server ${Number(id) + 1} Budget`] = ignored ? false : server.budget === undefined || server.budget === '' || Number(server.budget) < 1
        error[`Server ${Number(id) + 1} Type`] = ignored ? false : server.type === undefined;
    }
    setError(error);
}

const checkTasksForm = (knowledge, error, setError) => {
    for (let [id, task] of Object.entries(knowledge)) {
        error[`Task ${Number(id) + 1} Id`] = task.id === undefined || task.id === '';
        error[`Task ${Number(id) + 1} Agent Executor`] = task.agentExecutor === undefined || task.agentExecutor === '';
        error[`Task ${Number(id) + 1} Agent Demander`] = task.agentDemander === undefined || task.agentDemander === '';
        error[`Task ${Number(id) + 1} Computation Time`] = task.computationTime === undefined || task.computationTime === '' || (Number(task.computationTime) < 1);
        error[`Task ${Number(id) + 1} Residual Computation Time`] = task.residualComputationTime === undefined || task.residualComputationTime === '' || Number(task.residualComputationTime) > Number(task.computationTime);
        error[`Task ${Number(id) + 1} Arrival Time`] = task.arrivalTime === undefined || task.arrivalTime === '' || (Number(task.arrivalTime) < 0);
        error[`Task ${Number(id) + 1} Period`] = task.period === undefined || task.period === '' || Number(task.period) < Number(task.computationTime);
        error[`Task ${Number(id) + 1} Relative Deadline`] = task.relativeDeadline === undefined || task.relativeDeadline === '' || Number(task.relativeDeadline) < Number(task.period);
        if (Number(task.n_exec) !== -1) {
            error[`Task ${Number(id) + 1} Number of executions`] = task.n_exec === undefined || task.n_exec === '' || (Number(task.n_exec) < 1);
        }
        if (Number(task.firstActivationTime) !== -1) {
            error[`Task ${Number(id) + 1} First Activation Time`] = task.firstActivationTime === undefined || task.firstActivationTime === '' || (Number(task.firstActivationTime) < 0);
        }
        if (Number(task.lastActivationTime) !== -1) {
            error[`Task ${Number(id) + 1} Last Activation Time`] = task.lastActivationTime === undefined || task.lastActivationTime === '' || (Number(task.lastActivationTime) < 0);
        }
        error[`Task ${Number(id) + 1} Server`] = task.server === undefined;
    }
    setError(error);
}

const checkNeedsForm = (needs, error, setError, ignored) => {
    for (let [id, need] of Object.entries(needs)) {
        error[`Need ${Number(id) + 1} Agent Id`] = ignored ? false : need.agent_id === undefined;
        error[`Need ${Number(id) + 1} Release time`] = ignored ? false : need.releaseTime === undefined || need.releaseTime === '' || Number(need.releaseTime) < 0;
        error[`Need ${Number(id) + 1} Needed Task Release Time`] = ignored ? false : need.neededTaskRelease === undefined || need.neededTaskRelease === '' || Number(need.neededTaskRelease) < Number(need.releaseTime);
        error[`Need ${Number(id) + 1} Needed Task Deadline`] = ignored ? false : need.neededTaskDeadline === '' || need.neededTaskDeadline === undefined;
        error[`Need ${Number(id) + 1} Needed Task Executions`] = ignored ? false : need.neededTaskNExec === undefined || need.neededTaskNExec === '' || (Number(need.neededTaskNExec) !== -1 && Number(need.neededTaskNExec) < 0)
        error[`Need ${Number(id) + 1} Minimum Task Period`] = ignored ? false : Number(need.neededTaskTMin) < 0;
        error[`Need ${Number(id) + 1} Maximum Task Period`] = ignored ? false : Number(need.neededTaskTMax) < Number(need.neededTaskTMin);
        error[`Need ${Number(id) + 1} Needed Tasks`] = ignored ? false : need.neededTasks === undefined || need.neededTasks === [];
        error[`Need ${Number(id) + 1} Bidding window`] = ignored ? false : need.neededTimeout === undefined || need.neededTimeout === '' || Number(need.neededTimeout) < 0;
    }
    setError(error);
}

const checkForms = (ignored, config, agents, servers, knowledge, needs, error, setError) => {
    checkConfigForm(config, error, setError);
    checkAgentsForm(agents, error, setError, ignored.has(1));
    checkServersForm(servers, error, setError, ignored.has(2));
    checkTasksForm(knowledge, error, setError);
    checkNeedsForm(needs, error, setError, ignored.has(4));
}

const isValid = error => {
    for (let key in error) {
        if (error[key] === true)
            return false;
    }
    return true;
}

export {
    checkForms,
    isValid,
}