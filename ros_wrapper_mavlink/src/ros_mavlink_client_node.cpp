#include "ros_mavlink/ros_mavlink_client.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "ros_mavlink_client_node");
    ros::NodeHandle nh;

    RosMavlinkClient client(nh);
    client.run();

    return 0;
}