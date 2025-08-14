/**
 * *********************************************************
 *
 * @file: path_planner_factory.cpp
 * @brief: Create the planner with specifical parameters
 * @author: Yang Haodong
 * @date: 2025-02-16
 * @version: 1.0
 *
 * Copyright (c) 2025, Yang Haodong.
 * All rights reserved.
 *
 * --------------------------------------------------------
 *
 * ********************************************************
 */
#include "path_planner/utils/path_planner_factory.h"

// graph-based planner
#include "path_planner/path_planner_node.h"
#include "path_planner/graph_planner/astar_planner.h"
#include "path_planner/graph_planner/dstar_planner.h"


namespace rmp
{
namespace path_planner
{
/**
 * @brief Create and configure planner
 * @param nh ROS node handler
 * @param costmap_ros costmap ROS wrapper
 * @param planner_props planner property
 * @return bool true if create successful, else false
 */
bool PathPlannerFactory::createPlanner(ros::NodeHandle& nh, costmap_2d::Costmap2DROS* costmap_ros,
                                       PlannerProps& planner_props)
{
  double obstacle_factor;
  std::string planner_name;
  nh.param("planner_name", planner_name, (std::string) "astar");  // planner name
  nh.param("obstacle_factor", obstacle_factor, 0.5);              // obstacle factor

  if (planner_name == "astar")
  {
    planner_props.planner_ptr = std::make_shared<AStarPathPlanner>(costmap_ros, obstacle_factor);
    planner_props.planner_type = GRAPH_PLANNER;
  }

  else if (planner_name == "dstar")
  {
    planner_props.planner_ptr = std::make_shared<DStarPathPlanner>(costmap_ros, obstacle_factor);
    planner_props.planner_type = GRAPH_PLANNER;
  }

  else
  {
    R_ERROR << "Unknown planner name: " << planner_name;
    return false;
  }

  R_INFO << "Using path planner: " << planner_name;
  return true;
}
}  // namespace path_planner
}  // namespace rmp
