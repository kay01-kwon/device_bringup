#ifndef ROS_MAVLINK_CLIENT_HPP
#define ROS_MAVLINK_CLINET_HPP

#include <ros/ros.h>
#include <mavros_msgs/CommandLong.h>

using mavros_msgs::CommandLong;

class RosMavlinkClient
{
    public:
    
    RosMavlinkClient(ros::NodeHandle& nh);

    void run();

    ~RosMavlinkClient();

    private:

    ros::NodeHandle nh_;
    ros::ServiceClient command_long_service_;

    bool is_set_HIGHRES_IMU_rate_{false};

    bool is_set_ATTITUDE_QUATERNION_rate_{false};

    float HIGHRES_IMU_rate_{5000.0f}; // 5000 micro second interval

    float ATTITUDE_QUATERNION_rate_{5000.0f}; // 5000 micro second interval

    float RC_CHANNELS_rate_{10000.0f};  // 10,000 micro second (10 ms)

    float ODOMETRY_IN_rate_{10000.0f};  // 10,000 micro second (10 ms)

    float HIGHRES_IMU_msg_id_{105.0f};

    float ATTITUDE_QUATERNION_msg_id_{31.0f};

    float RC_CHANNELS_msg_id_{65.0f};

    float ODOMETRY_IN_msg_id_{331.0f};

    float MAV_CMD_SET_MESSAGE_INTERVAL_{511.0f};

};

#endif
