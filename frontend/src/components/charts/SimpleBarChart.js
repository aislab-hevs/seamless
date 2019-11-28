import React from 'react';
import {
  BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend, Cell,
} from 'recharts';

export default function SimpleBarChart(props) {
  const { data, field, colors } = props;

  return (
    <BarChart
      {...props}
      data={data}
      margin={{
        top: 5, right: 30, left: 20, bottom: 5,
      }}
    >
      <CartesianGrid strokeDasharray="3 3" />
      <XAxis dataKey="id" />
      <YAxis />
      <Tooltip />
      {/* <Legend /> */}
      <Bar barSize={30} dataKey={field}>
        {data.map((entry, index) =>
          <Cell
            key={`cell-${index}`}
            fill={colors[(Number(entry.id.split('_')[1]) % colors.length)]}
          />
        )}
      </Bar>
    </BarChart>
  );
}
