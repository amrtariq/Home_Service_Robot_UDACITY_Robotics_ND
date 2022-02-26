#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

visualization_msgs::Marker marker;
//position number
int pos_number=0, action_done=0;
void marker_check(const nav_msgs::Odometry::ConstPtr& msg)
{
  ROS_INFO("Seq: [%d]", msg->header.seq);
  ROS_INFO("Position-> x: [%f], Position-> y: [%f], Orientation-> Z: [%f]", msg->pose.pose.position.x, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
  ROS_INFO("Current State is: %d", pos_number);
  //if position reached
  if (action_done && (msg->pose.pose.position.x <= marker.pose.position.x+0.2) && (msg->pose.pose.position.x >= marker.pose.position.x-0.2) && (msg->pose.pose.position.y <= marker.pose.position.y+0.2) && (msg->pose.pose.position.y >= marker.pose.position.y-0.2)
    && (msg->pose.pose.orientation.z >= marker.pose.orientation.z-0.2) && (msg->pose.pose.orientation.z <= marker.pose.orientation.z+0.2))
  {
    pos_number++;
    action_done=0;
    ROS_INFO("state_Changed to: %d", pos_number);
  }
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  //declare publisher and subscriber
  ros::Subscriber marker_sub = n.subscribe("/odom", 10, marker_check);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  //define shape is cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  //while still final state not reached and ros is running ok
  while(ros::ok() && (pos_number<3))
  {

    
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();


    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one

    marker.ns = "add_markers";
    marker.id = 0;

    marker.type = shape;


    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;


    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
        // Set the scale of the marker -- 1x1x1 here means 1m on a side

    marker.scale.x = 0.1;
    marker.scale.y = 0.1;
    marker.scale.z = 0.1;


    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;


    marker.lifetime = ros::Duration();

    // wait untill there is subscriber for marker

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }

    //if all actions done keep track of odom messages
    while(1)
    {
      if(!action_done) break;
      ros::spinOnce();  // process queue data once per second
      r.sleep();
      ros::Duration(1.0).sleep();
    }
//check what state we are in
    switch(pos_number){

      case 0:
        if(!action_done){
          ROS_INFO("Marker set at Pickup Position Awaiting Robot");
          marker.pose.position.x = 1;
          marker.pose.position.y = 0;
          marker.pose.position.z = 2;
          marker.pose.orientation.x = 0.0;
          marker.pose.orientation.y = 0.0;
          marker.pose.orientation.z = 0.1;
          marker.pose.orientation.w = 0.0;
          action_done=1;
        }
        break;
      case 1:
        if(!action_done){

          marker.pose.position.x = 2;
          marker.pose.position.y = 0;
          marker.pose.position.z = 2;
          marker.pose.orientation.x = 0.0;
          marker.pose.orientation.y = 0.0;
          marker.pose.orientation.z = 0.1;
          marker.pose.orientation.w = 0.0;
          marker.action = visualization_msgs::Marker::DELETEALL;
          ROS_INFO("Pickup Pos Reached, Marker Deleted");
          action_done=1;
        }
        break;
      case 2:
        if(!action_done){
          ROS_INFO("Drop Position Reached, Marker set at Drop Position");
          marker.action = visualization_msgs::Marker::ADD;
          action_done=1;
          pos_number=3;
        }
        break;
      default:
        break;
    }

    marker_pub.publish(marker);
  }

  ROS_INFO("Marker Loop ended");
  //just for readablity sleep
  sleep(10);
}

