#include "ros_mavlink_client.hpp"

RosMavlinkClient::RosMavlinkClient(ros::NodeHandle& nh) : nh_(nh)
{
    nh_.getParam("HIGHRES_IMU_RATE", HIGHRES_IMU_rate_);
    nh_.getParam("ATTITUDE_QUATERNION_RATE", ATTITUDE_QUATERNION_rate_);
    nh_.getParam("RC_CHANNELS_RATE", RC_CHANNELS_rate_);

    command_long_service_ = nh_.serviceClient<mavros_msgs::CommandLong>
    ("/mavros/cmd/command", false);

}

void RosMavlinkClient::run()
{
    while(ros::ok())
    {
        mavros_msgs::CommandLong command_long_srv;

        command_long_srv.request.command = MAV_CMD_SET_MESSAGE_INTERVAL_;
        command_long_srv.request.param1 = HIGHRES_IMU_msg_id_;
        command_long_srv.request.param2 = HIGHRES_IMU_rate_;
        command_long_srv.request.confirmation = 0;

        if (!is_set_HIGHRES_IMU_rate_)
        {
            if (command_long_service_.call(command_long_srv))
            {
                is_set_HIGHRES_IMU_rate_ = true;
                ROS_INFO("Set HIGHRES_IMU message interval successfully.");
            }
            else
            {
                // ROS_ERROR("Failed to set HIGHRES_IMU message interval.");
            }
        }

        command_long_srv.request.command = MAV_CMD_SET_MESSAGE_INTERVAL_;
        command_long_srv.request.param1 = ATTITUDE_QUATERNION_msg_id_;
        command_long_srv.request.param2 = ATTITUDE_QUATERNION_rate_;

        if (!is_set_ATTITUDE_QUATERNION_rate_)
        {
            if (command_long_service_.call(command_long_srv))
            {
                is_set_ATTITUDE_QUATERNION_rate_ = true;
                ROS_INFO("Set ATTITUDE_QUATERNION message interval successfully.");
            }
            else
            {
                // ROS_ERROR("Failed to set ATTITUDE_QUATERNION message interval.");
            }
        }

        command_long_srv.request.command = MAV_CMD_SET_MESSAGE_INTERVAL_;
        command_long_srv.request.param1 = RC_CHANNELS_msg_id_;
        command_long_srv.request.param2 = RC_CHANNELS_rate_;

        command_long_service_.call(command_long_srv);

	command_long_srv.request.command = MAV_CMD_SET_MESSAGE_INTERVAL_;
	command_long_srv.request.param1 = ODOMETRY_IN_msg_id_;
	command_long_srv.request.param2 = ODOMETRY_IN_rate_;

	command_long_service_.call(command_long_srv);

        if(is_set_ATTITUDE_QUATERNION_rate_ && is_set_HIGHRES_IMU_rate_)
        {
            ROS_INFO("Both message intervals set successfully.");
            return;
        }

        ros::spinOnce();
    }

}

RosMavlinkClient::~RosMavlinkClient()
{
    // Destructor logic if needed
}
