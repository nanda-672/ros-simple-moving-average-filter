## Description
Measurements acquired by sensors can sometimes be noisy. Using this raw data directly for computation can cause unwanted robot behaviour. To alleviate this problem, some filters might be of use.

One such filter is **Simple Moving Average Filter**. This filter smooths out data by convolution. It averages *N* most recent measurements as described by the following equation:

<p align="center">
  <img src="images/image1.png" alt="image1"/>,
</p>

where *f_i* is the *i*-th data returned by the filter and *z_k* is the *k*-th data from the measurement stream.

For example, to calculate the 2nd data point returned by a filter of *N*=4, we get

<p align="center">
  <img src="images/image2.png" alt="image2"/>.
</p>

To illustrate:

<p align="center">
  <img src="images/image3.png" alt="image3"/>
</p>

## Your Task

Create 2 ROS nodes, one that acts as a sensor driver and another that is the filter. Computation graph will look something like this:

<p align="center">
  <img src="images/image4.png" alt="image4"/>
</p>

The details of each node are as follows:

### Sensor Driver Node
- Publishes message of type float64 to `/sensor_measurement` topic.
  - Message content is sensor measurement *z_i*.
  - Value of *z_i* is given by the formula: `z_i = sin(i * pi / 180) + g`, where `g` is a random number with Gaussian distribution of mean=0.0 and sigma=0.05.
- Node loop frequency is 100Hz.
- Implementation in Python.

### Filter Node
- Subscribes to `/sensor_measurement` topic.
- Publishes message of type float64 to `/sensor_measurement/filtered` topic.
  - Message content is *f_i*. Use *N*=5.
- Node loop frequency is 100Hz.
- Implementation in C++.