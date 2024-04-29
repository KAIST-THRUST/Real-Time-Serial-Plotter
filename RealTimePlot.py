import numpy as np
import serial
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore
from typing import List


class RealTimePlot:
    """
    A class used to plot real-time data from a serial port using PyQtGraph.

    Attributes
    ----------
    num_of_data : int
        The number of data series to plot.
    max_size : int
        The maximum number of data points to display on the plot.
    app : QApplication
        The PyQtGraph application.
    ser : Serial
        The serial port.
    win : GraphicsLayoutWidget
        The PyQtGraph window.
    plots : list
        The list of PlotItem objects.
    curves : list
        The list of PlotDataItem objects.
    datas_x : list
        The list of x data arrays.
    datas_y : list
        The list of y data arrays.
    update_rate : int
        The rate at which the plot updates, in milliseconds.
    time : float
        The current time, in seconds.
    timer : QTimer
        The timer that triggers the plot updates.

    Methods
    -------
    __init__(port: str, datas: List[str], window_title="Real-time Plotting", update_rate=50, max_size=250)
        Initializes the RealTimePlot object.
    __update() -> None
        Updates the plot with new data from the serial port.
    run() -> None
        Starts the PyQtGraph application.
    """

    def __init__(
        self,
        port: str,
        datas: List[str],
        window_title="Real-time Plotting",
        update_rate=50,
        max_size=250,
    ):
        """
        Initializes the RealTimePlot object.

        This method sets up the PyQtGraph application, opens the serial port, creates the PyQtGraph window,
        creates the plots and curves, initializes the data arrays, and starts the timer that triggers the plot updates.

        Parameters
        ----------
        port : str
            The name of the serial port to read data from.
        datas : List[str]
            The list of data series to plot.
        window_title : str, optional
            The title of the PyQtGraph window (default is "Real-time Plotting").
        update_rate : int, optional
            The rate at which the plot updates, in milliseconds (default is 50).
        max_size : int, optional
            The maximum number of data points to display on the plot (default is 250).
        """
        # Set the number of data series and the maximum number of data points
        self.num_of_data = len(datas)
        self.max_size = max_size

        # Create the PyQtGraph application
        self.app = pg.mkQApp()

        # Open the serial port
        self.ser = serial.Serial(port, 9600)

        # Create the PyQtGraph window
        self.win = pg.GraphicsLayoutWidget(show=True)
        self.win.resize(1200, 600)
        self.win.setWindowTitle(window_title)

        # Enable antialiasing for smoother plot lines
        pg.setConfigOptions(antialias=True)

        # Create the plots
        self.plots = []
        for i, data in enumerate(datas):
            self.plots.append(self.win.addPlot(title=data))
            if (i + 1) % 3 == 0:
                self.win.nextRow()

        # Create the curves
        self.curves = [plot.plot(pen="y") for plot in self.plots]

        # Initialize the data arrays
        self.datas_x = [np.array([])] * self.num_of_data
        self.datas_y = [np.array([])] * self.num_of_data

        # Set the update rate and initialize the current time
        self.update_rate = update_rate
        self.time = 0

        # Create the timer and connect it to the update method
        self.timer = QtCore.QTimer()

    def __update(self) -> None:
        """
        Updates the plot with new data from the serial port.

        This method is called every `update_rate` milliseconds by a QTimer object.
        It reads a line from the serial port, decodes it, and splits it into a list of float values.
        Each value is appended to the corresponding y data array, and the current time is appended to each x data array.
        If the length of a data array exceeds `max_size`, the oldest data point is removed.
        Finally, the data for each curve is updated with the new x and y data arrays.
        """
        # Check if there is data available to read from the serial port
        if self.ser.in_waiting > 0:
            # Read a line from the serial port
            line = self.ser.readline()

            # Decode the line and split it into a list of floats
            values = [float(value) for value in line.decode().strip().split(",")]

            # Append each value to the corresponding y data array
            self.datas_y = [
                np.append(data_y, value) for data_y, value in zip(self.datas_y, values)
            ]
            # Append the current time to each x data array
            self.datas_x = [np.append(data_x, self.time) for data_x in self.datas_x]

            # If the length of a data array exceeds max_size, remove the oldest data point
            if len(self.datas_y[0]) > self.max_size:
                self.datas_y = [data_y[1:] for data_y in self.datas_y]
                self.datas_x = [data_x[1:] for data_x in self.datas_x]

            # Update the data for each curve with the new x and y data arrays
            for curve, data_x, data_y in zip(self.curves, self.datas_x, self.datas_y):
                curve.setData(data_x, data_y)

        # Increment the current time by the update rate
        self.time += self.update_rate / 1000

    def run(self) -> None:
        """
        Display the plot to the pyqtgraph window.
        """
        self.timer.timeout.connect(self.__update)
        self.timer.start(self.update_rate)
        pg.exec()


if __name__ == "__main__":
    # Test code. Reads 6 values from the serial and plot each data.
    datas = [
        "sin",
        "cos",
        "constant",
        "sin(2x)",
        "square",
        "triangular",
    ]  # list of datas.
    plotter = RealTimePlot(port="COM2", datas=datas)
    plotter.run()
