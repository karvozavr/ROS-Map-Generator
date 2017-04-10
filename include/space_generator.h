/*
 * SpaceGenerator class used for generation of space containing rooms connected by corridors.
 *
 */

#ifndef ROS_MAP_GENERATOR_SPACE_GENERATOR_H
#define ROS_MAP_GENERATOR_SPACE_GENERATOR_H

#include <vector>
#include <algorithm>

#include "room.h"

class SpaceGenerator {
 public:
  // separates overlapping rooms (allowing to overlap by `padding`)
  void separateRooms(int64_t padding = 1);

 private:
  std::vector<Room> rooms_;
};


#endif //ROS_MAP_GENERATOR_SPACE_GENERATOR_H
