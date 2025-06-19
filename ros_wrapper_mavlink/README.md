# mavros for use

This package modifed the launch, yaml files of MAVROS

to reduce the computational load.

Loads of pluginlists has been blacklisted.

## How to launch the node

```
roslaunch ros_mavlink px4.launch
```

## How to increase the rate of streaming

Just run the node to increase the frequency of corresponding msgs.

```
rosrun ros_mavlink ros_mavlink_client
```

This node call the service to the mavros and then set the frequency.

Then, it terminates itself when receiving true result for both commands.

The execution of the node is equivalent to send rosservice like the following.

Command for MAV_CMD_SET_MESSAGE_INTERVAL : 511

Message id for HIGHRES_IMU : 105

Message id for ATTITUDE_QUATERNION : 31

```
rosservice call /mavros/cmd/command "{broadcast: false, command: 511, confirmation: 0, param1: 105.0, param2: 5000.0, param3: 0.0,
  param4: 0.0, param5: 0.0, param6: 0.0, param7: 0.0}"
```

```
rosservice call /mavros/cmd/command "{broadcast: false, command: 511, confirmation: 0, param1: 31.0, param2: 5000.0, param3: 0.0,
  param4: 0.0, param5: 0.0, param6: 0.0, param7: 0.0}"
```

