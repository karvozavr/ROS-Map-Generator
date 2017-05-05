/*
 * SpaceGenerator class used for generation of space containing halls connected by corridors.
 *
 */

#ifndef ROS_MAP_GENERATOR_SPACE_GENERATOR_H
#define ROS_MAP_GENERATOR_SPACE_GENERATOR_H

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include "graph.h"
#include "room.h"
#include "randomizer.h"

class RosNavigationEnvironment {
 public:
  struct VertexStorage {
    Room *room;
  };

  /**
   * Constructor of environment will randomly generate environment of parameters
   * @param amount amount of Rooms
   * @param min_size minimal possible size of a room
   * @param max_size maximal possible size of a room
   * @param corridor_width width of corridors
   * @param width width of navigation environment
   * @param height height of navigation environment
   */
  RosNavigationEnvironment(size_t amount,
                           int64_t min_size,
                           int64_t max_size,
                           int64_t corridor_width,
                           size_t width,
                           size_t height,
                           Randomizer<int64_t> *random,
                           bool obstacles = true);

  const std::vector<Room> &rooms() const { return rooms_; };

  /**
   * @return width of navigation environment
   */
  size_t width() const { return width_; }

  /**
   * @return height of navigation environment
   */
  size_t height() const { return height_; }

 private:
  /**
   * separates overlapping rooms
   * @param padding allow rooms to overlap by `padding`
   */
  void separateRooms(int64_t padding = 1);

  /**
   * Create relative neighborhood graph (RNG) of rooms
   */
  void createRNG();

  /**
   * Connect rooms with hallways
   */
  void connectRooms();

  /**
   * removes rooms that are overbound
   */
  void removeOverboundingRooms();

  std::vector<Room> rooms_;
  Graph<Room *> room_graph_;

  size_t width_;
  size_t height_;
  int64_t corridor_width_;

  Randomizer<int64_t> *random_;
};


#endif //ROS_MAP_GENERATOR_SPACE_GENERATOR_H
