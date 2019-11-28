import React from 'react'
import {
  FormControl,
  Select,
  InputLabel,
  MenuItem,
  Menu,
  FormHelperText
} from '@material-ui/core';
import PropTypes from 'prop-types';

export default function CustomSelect(props) {
  const { className, label, name, value, options } = props;

  return (
    <FormControl className={className}>
      <InputLabel 
      shrink={props.shrinked ? Boolean(props.shrinked) : undefined} // workaround to error 'received value for non-boolean attribute
      error={props.error} 
      htmlFor={name}>{label}
      </InputLabel>
      <Select
        {...props}
        inputProps={{
          name: `${name}`,
          id: `${name}`,
          value: `${String(value) || ''}` //if I use int it doesn't show the 0th option -.-"
        }}
      >
        {/* <MenuItem value={-1}>None</MenuItem> */}
        {Object.keys(options).map((key, index) => {
          return <MenuItem
            key={index}
            value={options[key]}>{key}
          </MenuItem>
        })}
      </Select>
      {props.helpertext && <FormHelperText error={props.error}>{props.helpertext}</FormHelperText>}
    </FormControl>
  )
}