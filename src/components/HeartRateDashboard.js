import React from 'react';
import { Line } from 'react-chartjs-2';
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
} from 'chart.js';

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

const HeartRateDashboard = () => {
  // Sample data - replace with real data
  const heartRateData = {
    labels: ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10'],
    datasets: [
      {
        label: 'Heart Rate (BPM)',
        data: [65, 70, 75, 80, 85, 90, 95, 100, 105, 110],
        borderColor: 'rgb(255, 99, 132)',
        backgroundColor: 'rgba(255, 99, 132, 0.5)',
        tension: 0.4,
      },
    ],
  };

  const accelerometerData = {
    labels: ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10'],
    datasets: [
      {
        label: 'X-axis',
        data: [0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0],
        borderColor: 'rgb(75, 192, 192)',
        backgroundColor: 'rgba(75, 192, 192, 0.5)',
        tension: 0.4,
      },
      {
        label: 'Y-axis',
        data: [0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1],
        borderColor: 'rgb(255, 159, 64)',
        backgroundColor: 'rgba(255, 159, 64, 0.5)',
        tension: 0.4,
      },
      {
        label: 'Z-axis',
        data: [0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2],
        borderColor: 'rgb(153, 102, 255)',
        backgroundColor: 'rgba(153, 102, 255, 0.5)',
        tension: 0.4,
      },
    ],
  };

  const options = {
    responsive: true,
    plugins: {
      legend: {
        position: 'top',
      },
      title: {
        display: true,
        text: 'Heart Rate Monitor Dashboard',
      },
    },
    scales: {
      y: {
        beginAtZero: true,
      },
    },
  };

  return (
    <div className="p-6 bg-gray-100 min-h-screen">
      <div className="max-w-7xl mx-auto">
        <div className="grid grid-cols-1 md:grid-cols-3 gap-6 mb-6">
          {/* Heart Rate Zones */}
          <div className="bg-white p-6 rounded-lg shadow-md">
            <h2 className="text-xl font-semibold mb-4">Heart Rate Zones</h2>
            <div className="space-y-4">
              <div className="bg-red-100 p-4 rounded">
                <h3 className="font-medium">Zone 1: Des</h3>
                <p className="text-gray-600">50-60 BPM</p>
              </div>
              <div className="bg-yellow-100 p-4 rounded">
                <h3 className="font-medium">Zone 2: Moderate</h3>
                <p className="text-gray-600">60-70 BPM</p>
              </div>
              <div className="bg-green-100 p-4 rounded">
                <h3 className="font-medium">Zone 3: Active</h3>
                <p className="text-gray-600">70+ BPM</p>
              </div>
            </div>
          </div>

          {/* Current Heart Rate */}
          <div className="bg-white p-6 rounded-lg shadow-md">
            <h2 className="text-xl font-semibold mb-4">Current Heart Rate</h2>
            <div className="text-center">
              <div className="text-6xl font-bold text-red-500">75</div>
              <p className="text-gray-600 mt-2">Beats Per Minute</p>
            </div>
          </div>

          {/* Accelerometer Data */}
          <div className="bg-white p-6 rounded-lg shadow-md">
            <h2 className="text-xl font-semibold mb-4">Accelerometer Data</h2>
            <div className="space-y-4">
              <div>
                <h3 className="font-medium">X-axis</h3>
                <p className="text-gray-600">0.5 g</p>
              </div>
              <div>
                <h3 className="font-medium">Y-axis</h3>
                <p className="text-gray-600">0.3 g</p>
              </div>
              <div>
                <h3 className="font-medium">Z-axis</h3>
                <p className="text-gray-600">0.8 g</p>
              </div>
            </div>
          </div>
        </div>

        {/* Charts */}
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
          <div className="bg-white p-6 rounded-lg shadow-md">
            <h2 className="text-xl font-semibold mb-4">Heart Rate History</h2>
            <Line data={heartRateData} options={options} />
          </div>
          <div className="bg-white p-6 rounded-lg shadow-md">
            <h2 className="text-xl font-semibold mb-4">Accelerometer History</h2>
            <Line data={accelerometerData} options={options} />
          </div>
        </div>
      </div>
    </div>
  );
};

export default HeartRateDashboard; 