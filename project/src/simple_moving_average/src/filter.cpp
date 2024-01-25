#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <list>
#include <numeric>

void callback(const std_msgs::Float64::ConstPtr& f)
{
    double z;
    double sum;
    std::list<double> mylist;

    while(mylist.size() != 5)
    {
        mylist.push_back(f->data);
    }

    sum = std::accumulate(std::begin(mylist), std::end(mylist), 0.0);

    z = sum/5;

    if (mylist.size() == 5)
    {
        ROS_INFO("%f", z);
        mylist.pop_front();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "filter_node");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("sensor_measurement", 100, callback);

    ros::spin();

    return 0;
}