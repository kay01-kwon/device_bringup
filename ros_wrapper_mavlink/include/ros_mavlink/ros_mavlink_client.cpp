#include "ros_mavlink_client.hpp"

RosMavlinkClient::RosMavlinkClient(ros::NodeHandle& nh) : nh_(nh)
{
    // nh_.getParam("HIGHRES_IMU_RATE", HIGHRES_IMU_rate_);
    // nh_.getParam("ATTITUDE_QUATERNION_RATE", ATTITUDE_QUATERNION_rate_);
    // nh_.getParam("RC_CHANNELS_RATE", RC_CHANNELS_rate_);

    command_long_service_ = nh_.serviceClient<mavros_msgs::CommandLong>
    ("/mavros/cmd/command", false);

}

void RosMavlinkClient::run()
{
    std::string msg_name;
    while(ros::ok())
    {
        mavros_msgs::CommandLong command_long_srv;

        // 1. Set HIGHRES_IMU message interval
        msg_name = "HIGHRES_IMU";
        command_long_srv.request.command = MAV_CMD_SET_MESSAGE_INTERVAL_;
        command_long_srv.request.param1 = HIGHRES_IMU_msg_id_;
        command_long_srv.request.param2 = HIGHRES_IMU_rate_;
        command_long_srv.request.confirmation = 0;
        call_service_(command_long_srv, is_set_HIGHRES_IMU_rate_, msg_name);

        // 2. Set ATTITUDE_QUATERNION message interval
         msg_name = "ATTITUDE_QUATERNION";
        command_long_srv.request.param1 = ATTITUDE_QUATERNION_msg_id_;
        command_long_srv.request.param2 = ATTITUDE_QUATERNION_rate_;
        command_long_srv.request.confirmation = 0;
        call_service_(command_long_srv, is_set_ATTITUDE_QUATERNION_rate_, msg_name);

        // 3. Set RC_CHANNELS message interval
        msg_name = "RC_CHANNELS";
        command_long_srv.request.param1 = RC_CHANNELS_msg_id_;
        command_long_srv.request.param2 = RC_CHANNELS_rate_;
        command_long_srv.request.confirmation = 0;
        call_service_(command_long_srv, is_set_RC_CHANNELS_rate_, msg_name);

        // 4. Set Local_Position_Odom message interval
        msg_name = "Local_Position_Odom";
	    command_long_srv.request.param1 = Local_Position_Odom_msg_id_;
	    command_long_srv.request.param2 = Local_Position_Odom_rate_;
        command_long_srv.request.confirmation = 0;
        call_service_(command_long_srv, is_set_Local_Position_Odom_rate_, msg_name);

        if (is_set_HIGHRES_IMU_rate_ && is_set_ATTITUDE_QUATERNION_rate_ && is_set_RC_CHANNELS_rate_ && is_set_Local_Position_Odom_rate_)
        {
            ROS_INFO("All message intervals have been set. Exiting...");
            return;
        }

        ros::spinOnce();
    }

}

bool RosMavlinkClient::call_service_(CommandLong& command_long_srv, bool &is_set_rate, const std::string &msg_name)
{
    if (!is_set_rate)
    {
        if (command_long_service_.call(command_long_srv))
        {
            is_set_rate = true;
            ROS_INFO("Set %s message interval successfully.", msg_name.c_str());
            return true;
        }
        else
        {
            ROS_ERROR("Failed to set %s message interval.", msg_name.c_str());
            return false;
        }
    }
    return false;
}

RosMavlinkClient::~RosMavlinkClient()
{
    // Destructor logic if needed
}
