import React from 'react';
import {
  BarChart, Bar, XAxis, YAxis, CartesianGrid, Tooltip, Legend, Cell,
} from 'recharts';

// const CustomTooltip = ({ active, payload, label }) => {
//   if (active) {
//     console.log(payload);
//     return (
//       <div className="custom-tooltip">
//         <p className="label">{`${label} : ${payload[0].dmr}`}</p>
//       </div>
//     );
//   }
// }

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
      <YAxis  domain={[0,1]}/>
      <Tooltip />
      {/* {props.keys &&
        <Tooltip content={<CustomTooltip />} />
      } */}
      {/* <Legend /> */}
      <Bar barSize={30} dataKey={field}>
        {data.map((entry, index) =>
          <Cell
            key={`cell-${index}`}
            fill={colors[(Number(entry.id.split('_')[1]) % colors.length)]}
          />
        )}
      </Bar>
      {/* {props.keys &&
        props.keys.map(key => <Bar barSize={15} dataKey={key} />)
      } */}
    </BarChart>
  );
}
