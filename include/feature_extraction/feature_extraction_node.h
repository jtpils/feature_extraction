/*
 * Header file for feature extraction node
 *
 * Dan Pierce
 * 2017-06-01
 */
#ifndef _FEATURE_EXTRACTION_NODE_H_
#define _FEATURE_EXTRACTION_NODE_H_
// ROS
#include <ros/ros.h>
#include <pcl_ros/point_cloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/Imu.h>
#include <pcl_conversions/pcl_conversions.h>
 #include "tf/transform_datatypes.h"
// STL
#include <iostream>
// PCL
#include <pcl/point_types.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/keypoints/harris_3d.h>
#include <pcl/features/normal_3d.h>
#include <pcl/features/shot.h>
#include <pcl/filters/conditional_removal.h>
#include <pcl/common/transforms.h>

/*! /brief Primary class for the feature extraction node class
*
*/
class FeatureExtractionNode
{

    typedef pcl::PointXYZI Point;
    typedef pcl::PointCloud<Point> PointCloud;

    typedef pcl::SHOT352 Descriptor;
    typedef pcl::PointCloud<Descriptor> DescriptorCloud;
    
  public:

    FeatureExtractionNode();
    ~FeatureExtractionNode();

  private:

    void printRosParameters (void);

    void rotateCloud (const PointCloud &cloud,PointCloud::Ptr transformed_cloud);

    void filterCloud (PointCloud::Ptr cloud);

    void getKeypointIndices (const PointCloud &cloud);

    void cloudCallback(const sensor_msgs::PointCloud2ConstPtr& msg);
    void imuCallback(const sensor_msgs::ImuConstPtr& msg);
    
    // --- Publisher
    ros::Publisher feature_pub;         // Feature publisher
    ros::Publisher kp_pub;              // Keypoint publisher
    ros::Publisher filt_pub;            // Filtered point cloud publisher

    // --- Subscribers
    ros::Subscriber pc_sub;             // Point cloud subscriber
    ros::Subscriber imu_sub;            // IMU subscriber (for roll/pitch)
    
    // --- Class variables
    // Pass through filter
    double zMin,zMax,xMin,xMax,yMin,yMax; // Bounds of point cloud pass through filter
    double roll,pitch;                  // Roll/pitch estimate for rotating point cloud to local-level frame
    // Normal estimation
    int nnNormal;                       // number of neighbors used to estimate surface normal
    // Detector
    int kpNumThreads;                   // number of threads in calculating harris keypoints
    bool kpRefine;                      // keypoint refine boolean
    bool kpNonMaxSupression;            // keypoint detection non max supression boolean
    double kpThreshold;                 // keypoint detection threshold for non max supression 
    double kpRadius;                    // radius (in meters) for gathering neighbors
    
    // Descriptor


};

#endif