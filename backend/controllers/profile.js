const handleProfileGet = db => (req, res) => {
    const { id } = req.params;
    db.select('*').from('users').where({ id }).then(user => {
        if (user.length) {
            res.json(user[0]);
        } else {
            res.status(404).json('Not found');
        }
    })
        .catch(err => res.status(400).json('Error getting user', err));
}

const handleProfileUpdate = (req, res, db) => {
    const { id } = req.params;
    const { name, age, pet } = req.body.formInput;
    db('users')
        .where({ id })
        .update({ name })
        .then(resp => {
            if (resp) {
                res.json('success');
            } else {
                res.status(400).json('unable to update');
            }
        })
        .catch(err =>res.status(400).json('error updating user'));
}

module.exports = {
    handleProfileGet,
    handleProfileUpdate
}