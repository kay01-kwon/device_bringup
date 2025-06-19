# device_brigup


## Camera launch

Before executing vins fusion,

it is necessary to run D435 (camera) and px 6x mini (IMU).

To launch the camera node,

```
roslaunch d435i_bringup d435i.launch
```

Additionally, through urdf format, robot state publisher, 

and joint state publisher,

it bridges camera (the frame of vins fusion) and camera_link (the frame of D435).

The reason why the generation of joint is performed is to get depth image

in the world frame.

## Pixhawk 6x mini launch

Firstly, launch the pixhawk 6x mini to get linear acceleration and

angular velocity expressed by imu frame.


```
roslaunch ros_mavlink px4.launch
```

To set the frequency of the IMU data,

run the client node.


```
rosrun ros_mavlink ros_mavlink_client
```

Check if the rate of IMU msg is approximately 200 Hz.

```
rostopic hz /mavros/imu/data_raw
```