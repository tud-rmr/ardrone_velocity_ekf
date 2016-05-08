#ifndef vrep_connection_HPP
#define vrep_connection_HPP

#include <queue>
#include <ros/ros.h>
#include "std_msgs/Float32.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include <ardrone_autonomy/Navdata.h>
#include "tf/transform_datatypes.h"

struct Odom
{

  // The geometry_msgs::Twist
 nav_msgs::Odometry odom_;

  // The real-valued time,
  ros::Time time_;

  // We want earlier times to have greater priority
  bool operator()(const Odom &a, const Odom &b)
  {
      return a.time_.toSec() > b.time_.toSec();
  }

  Odom() :
    time_(0)
  {
  }
};
struct Twist
{

  // The geometry_msgs::Twist
  geometry_msgs::Twist control_;

  // The real-valued time,
  ros::Time time_;

  // We want earlier times to have greater priority
  bool operator()(const Twist &a, const Twist &b)
  {
      return a.time_.toSec() > b.time_.toSec();
  }

  Twist() :
    time_(0)
  {
  }
};

typedef std::priority_queue<Odom, std::vector<Odom>, Odom> OdomQueue;
typedef std::priority_queue<Twist, std::vector<Twist>, Twist> TwistQueue;

ros::Subscriber cmd_sub, vrep_sub;
ros::Publisher cmd_pub, vrep_pub, nav_pub;

OdomQueue odomqueue;
TwistQueue twistqueue;

void convert_to_nav(const nav_msgs::Odometry odo);


void command_to_vrep(ros::Time curTime);


void delay_to_rl(ros::Time curTime);


void CmdVelCallback(const geometry_msgs::Twist msg);


void VrepCallback(const nav_msgs::Odometry msg);

#endif
