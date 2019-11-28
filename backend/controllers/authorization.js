const redis = require('redis');
const jwt = require('jsonwebtoken');

// setup Redis:
const redisClient = redis.createClient(process.env.REDIS_URI);

const requireAuth = (req, res, next) => {
    const { authorization } = req.headers;
    if (!authorization) {
        return res.status(401).json('Unauthorized');
    }
    return redisClient.get(authorization, (err, reply) => {
        if (err || !reply) {
            return res.status(401).json('Unauthorized');
        }
        return next();
    })
}

const getAuthTokenId = (req, res) => {
    ;
    const { authorization } = req.headers;
    return redisClient.get(authorization, (err, reply) => {
        if (err || !reply) {
            return res.status(400).json('Unauthorized');
        }
        return res.json({ id: reply });
    })
}

const signToken = (email) => {
    const jwtPayload = { email };
    return jwt.sign(jwtPayload, 'JWT-SECRET', { expiresIn: '2 days' });
}

const setToken = (key, value) => {
    return Promise.resolve(redisClient.set(key, value));
}

const createSessions = (user) => {
    // JWT Token, return user data
    const { email, id } = user;
    const token = signToken(email);
    return setToken(token, id)
        .then(() => {
            return { success: 'true', userId: id, token }
        })
        .catch(console.log);
}

module.exports = {
    requireAuth,
    getAuthTokenId,
    signToken,
    setToken,
    createSessions
}