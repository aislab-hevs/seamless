import React from 'react';
import {
  LineChart, Line, XAxis, YAxis, CartesianGrid, Tooltip, Legend,
} from 'recharts';

export default function MergedUtilChart(props) {
  const { data, colors } = props;

  return (
    <LineChart
      {...props}
      data={data}
      margin={{
        top: 5, right: 30, left: 20, bottom: 5,
      }}
    >
      <CartesianGrid strokeDasharray="3 3" />
      <XAxis dataKey='time' type='number' />
      <YAxis />
      <Tooltip />
      <Legend />
      <Line
        dot={false}
        dataKey='utilization'
        stroke={colors[0]}
        activeDot={{ r: 6 }}
        connectNulls
        type="step"
      />
      <Line
        // dot={false}
        dataKey='potential utilization'
        stroke={colors[1]}
        activeDot={{ r: 6 }}
        connectNulls
        type="step"
      />
    </LineChart>
  );
}
