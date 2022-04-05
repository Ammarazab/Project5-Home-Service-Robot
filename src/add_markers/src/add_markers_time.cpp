#include <ros/ros.h>
#include <visualization_msgs/Marker.h>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "goal_marker");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);


  uint32_t shape = visualization_msgs::Marker::SPHERE;;

  while (ros::ok())
  {
  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;
  
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  marker.pose.orientation.w = 1.0;
  marker.scale.x = 0.4;
  marker.scale.y = 0.4;
  marker.scale.z = 0.4;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;
  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    
      ROS_INFO("adding pickup marker");
      sleep(5);
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = 10;
      marker.pose.position.y = 4;
      marker_pub.publish(marker);
      
      
      sleep(5);
      ROS_INFO("deleting pickup marker");
      marker.action = visualization_msgs::Marker::DELETE;
      
      marker_pub.publish(marker);
      
      sleep(5.0);
      ROS_INFO("adding drop off marker");
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = -10;
      marker.pose.position.y = 1.8;
      marker_pub.publish(marker);
    

    
    
    ros::spinOnce();
  }
  return 0;
}
