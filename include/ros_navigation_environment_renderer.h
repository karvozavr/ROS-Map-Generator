/*
 * ROS map generator
 *  ros_navigation_environment_renderer.h
 *
 * Created by Dmitriy Abramov (karvozavr@gmail.com) May, 2017
 */

#ifndef ROS_MAP_GENERATOR_ROS_MAP_PRINTER_H
#define ROS_MAP_GENERATOR_ROS_MAP_PRINTER_H

#include <iostream>
#include "ros_navigation_environment.h"

class RosNavigationEnvironmentRenderer {
 public:
  RosNavigationEnvironmentRenderer(std::ostream &out_stream, RosNavigationEnvironment &environment)
      : out_stream_(out_stream),
        environment_(environment),
        space(environment_.width(), std::vector<uint8_t>(environment_.height(), 0)) {}


  void save_to_pgm();

 private:
  void render();
  std::ostream &out_stream_;
  RosNavigationEnvironment &environment_;
  std::vector<std::vector<uint8_t>> space;

  enum Color {
    black = 0,
    gray = 204,
    white = 255
  };
};


#endif //ROS_MAP_GENERATOR_ROS_MAP_PRINTER_H
