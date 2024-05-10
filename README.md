# Real Time Serial Plotter

## Introduction

The Real Time Serial Plotter is a Python application designed to plot 
real-time data received from a serial port. It uses PyQtGraph for plotting 
and pySerial for serial communication, making it possible to visualize data 
from devices using serial port like arduino.

## Features

- Real-time plotting of data received from a serial port
- Supports multiple data series plotting
- Adjustable plot update rate
- Adjustable maximum number of data points displayed
- Adjustable serial data packet style

## Installation

1. Clone or download this repository to your local machine.
2. Install the required Python packages if they are not installed 
in your local computer.

```bash
pip install pyqtgraph pyserial
```

## Usage

To use this application, move `RealTimePlot.py` to your project directory 
and import the `RealTimePlot` class to your project file. For example, 

```python
from RealTimePlot import RealTimePlot

# Test code. Reads 6 values from the serial and plot each data.
# Modify the parameters of the `RealtimePlot` to fit your project.
datas = [
    "pressure1",
    "pressure2",
    "pressure3",
    "temparature1",
    "temparature2",
    "flow meter",
]  # list of datas.
plotter = RealTimePlot(data_set=datas, port="COM2")
plotter.run()
```

This example will show 6 graphs in your screen if input data comes from
the serial port `COM2` properly.
