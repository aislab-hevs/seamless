import React from 'react';
import {
  ScatterChart,
  Scatter,
  XAxis,
  YAxis,
  ZAxis,
  Tooltip,
  LineChart,
  Line,
  Legend,
  Cell,
  ComposedChart,
  CartesianGrid,
} from 'recharts';
import { makeStyles } from '@material-ui/styles';

const useStyles = makeStyles(theme => ({
  'recharts-scatter': {
    transform: 'translate(15px, 0px)'
  }
}))

const parseDomain = (data) => [
  0,
  Math.max(
    Math.max.apply(null, data.map(entry => entry.value)),
  ),
];

const CustomTooltip = ({ active, payload, label }) => {
  if (active) {
    return (
      <div className="custom-tooltip">
        <p className="label">{`${label} : ${payload[0].value}`}</p>
        <p className="desc">Anything you want can be displayed here.</p>
      </div>
    );
  }
}

export default function GanttScatterChart(props) {

  const { data, colors, ratio } = props;
  const domain = props.domain > 30 ? props.domain : 30;
  const range = [0, 900];

  const classes = useStyles();

  return (
    <div>
      {Object.keys(data).map((key) => {
        return (
          <ComposedChart
            data={data[key]}
            key={key}
            width={30 * domain}
            height={(ratio - 1) * 50}
            margin={{
              top: (ratio - 2) * 50, right: 15, bottom: 0, left: 10,
            }}
          >
            <XAxis
              type="number"
              dataKey="time"
              interval={0}
              tick={{ fontSize: 10, transform: 'translate(0, 2)' }}
              allowDecimals={false}
              // tickLine={{ transform: 'translate(14, 0)' }}
              // allowDataOverflow={true} // makes bars thinner
              padding={{ bottom: 20 }}
              tickCount={domain + 1} />
            <YAxis
              type="number"
              dataKey="index"
              name={key}
              height={10}
              width={80}
              tick={false}
              tickLine={false}
              axisLine={false}
              label={{ value: `${key}`, position: 'insideRight', offset: 30 }}
            />
            <ZAxis
              type="number"
              dataKey="value"
              domain={domain}
              range={range}
            />
            <Scatter
              className={classes["recharts-scatter"]}
              isAnimationActive={false}
              data={data[key]}
              shape='square'
            >
              {data[key].map((entry, index) =>
                <Cell
                  key={`cell-${index}`}
                  fill={colors[Number(entry.task) % colors.length]}

                />
              )}
            </Scatter>
            <Tooltip cursor={false} offset={0} />
            <Line
              isAnimationActive={false}
              dataKey='budget'
              stroke='#000000'
              activeDot={{ r: 6 }}
              connectNulls
              type="stepBefore"
            />}
          </ComposedChart>
        )
      }
      )}
    </div>
  );
}

