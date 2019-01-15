#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//#include <node_handle.h>
#include <vector>

struct ParsedLine{
    geometry_msgs::Twist t;
    double time;
};

ParsedLine parse_line(const auto &line) {
    ParsedLine l;
    l.time << line;
    l.t.linear.x << line;
    l.t.linear.y << line;
    l.t.linear.z << line;
    l.t.angular.x << line;
    l.t.angular.y << line;
    l.t.angular.z << line;
    return l;
}

auto callback = [auto &pub, auto &twists](auto) {
    pub.publish(twists.back());
    twists.pop_back();
}

void run() {
    ros::init(argc, argv, "sim_instr");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<Twist>("cmd_vel", 1000);

    std::vector<geometry_msgs::Twist> twists;
    std::vector<ros::Timer> timers;

    for(const auto &line : file) {
        ParsedLine pline = parse_line(line);
        twists.push_back(pline.t);
        timers.push_back(nh.createTimer(ros::Duration(pline.time), callback, true));
    }
}

int main(int argc, char** argv) {
    run();
}
