import { useState, useEffect } from 'react';

const useForm = (callback) => {

  const [values, setValues] = useState({});

  const handleSubmit = (event) => {
    if (event) event.preventDefault();
    callback(event);
  };

  // passing prop enables to choose what property of the input field
  // should be stores (e.g. for switches we store the prop 'checked' instead of 'value')
  const handleChange = prop => event => {
    event.persist();
    setValues(values => ({ ...values, [event.target.name]: event.target[prop] }));
  };

  return {
    handleChange,
    handleSubmit,
    values,
    setValues
  }
};

export default useForm;