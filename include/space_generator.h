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
  SpaceGenerator(size_t amount, int64_t size, int64_t coordinate);
  // separates overlapping rooms (allowing to overlap by `padding`)
  std::vector<Room> &rooms();

 private:
  void separateRooms(int64_t padding = 1);
  std::vector<Room> rooms_;
};


#endif //ROS_MAP_GENERATOR_SPACE_GENERATOR_H
