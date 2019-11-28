import React from 'react';
import {
  LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend,
} from 'recharts';

export default function SimpleChart(props) {
  const { data, ids, value, field, colors, multiline, type } = props;

  const getLines = (ids) => {
    const lines = [];
    for (let [index, id] of ids.entries()) {
      lines.push(<Line
        dot={props.dot}
        key={id}
        dataKey={`${value}${id}`}
        stroke={colors[id % colors.length]} // use 'index' to always start from the first color
        activeDot={{ r: 6 }}
        connectNulls
        type={type}
      />)
    }
    return lines;
  }

  return (
    <LineChart
      {...props}
      data={data}
      margin={{
        top: 5, right: 30, left: 20, bottom: 5,
      }}
    >
      <CartesianGrid strokeDasharray="3 3" />
      <XAxis dataKey={field} type='number' />
      <YAxis />
      <Tooltip />
      <Legend />
      {multiline
        ? getLines(ids)
        : <Line
          dot={props.dot}
          dataKey={`${value}`}
          stroke={colors[0]}
          activeDot={{ r: 6 }}
          connectNulls
          type={type}
        />}
    </LineChart>
  );
}
