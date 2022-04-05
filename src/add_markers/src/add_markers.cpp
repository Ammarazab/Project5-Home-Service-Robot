#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <math.h>

double r_x;
double r_y;
 bool reach_pk_zone =false ;
void r_p_Callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &poses)
{
  r_x = poses->pose.pose.position.x;
  r_y = poses->pose.pose.position.y;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "goal_marker");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber odom_sub = n.subscribe("/amcl_pose", 10, r_p_Callback);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;
  marker.lifetime = ros::Duration();
  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  marker.pose.orientation.w = 1.0;
  marker.scale.x = 0.4;
  marker.scale.y = 0.4;
  marker.scale.z = 0.4;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 0.0f;
  marker.color.a = 1.0;
  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  while (ros::ok())
  {

    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;

        ROS_WARN_ONCE("Please create a subscriber to the marker");
        sleep(1);
      }
    }
    double pickup_vaiance = sqrt(pow(r_x - 10, 2) + pow(r_y - 4, 2));

    double droppff_variance = sqrt(pow(r_x - -10, 2) + pow(r_y - 1.8, 2));
    bool pk_marker = false;
   
  
    
    
      
    
      
      
      if (reach_pk_zone == false){
         ROS_INFO("adding pickup marker");
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = 10;
      marker.pose.position.y = 4;
      marker_pub.publish(marker);
      
      
      
      
      }

       if (pickup_vaiance < 0.5)
      {
        pk_marker = true;
        reach_pk_zone = true;
      // }

      // if (pk_marker == true)
      // {
        ROS_INFO("removing pickup marker");
        
        marker.action = visualization_msgs::Marker::DELETE;
        // marker.pose.position.x = 10;
        // marker.pose.position.y = 4;
        marker_pub.publish(marker);
        sleep(5.0);
        // reach_pk_zone++;
      }
      // else if (droppff_variance > 0.5 && reach_pk_zone == 2)
      // {
      //   ROS_INFO("deleting pickup marker");
      //   marker.action = visualization_msgs::Marker::DELETE;
      //   marker_pub.publish(marker);
      //   sleep(5.0);
      // }
      else if (droppff_variance < 0.3)
      {
        ROS_INFO("adding drop off marker");
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = -10;
        marker.pose.position.y = 1.8;
        marker_pub.publish(marker);
      }
    
    ros::spinOnce();
  }
  return 0;
}
