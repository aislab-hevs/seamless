/*
 * Copyright (c) 2020, HES-SO Valais-Wallis (https://www.hevs.ch)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

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
    <div style={{ marginBottom: '40px' }}>
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
            <Tooltip cursor={false} offset={10} />
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

