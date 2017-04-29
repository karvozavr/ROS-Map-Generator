/*
 * SpaceGenerator class used for generation of space containing rooms connected by corridors.
 *
 */

#ifndef ROS_MAP_GENERATOR_SPACE_GENERATOR_H
#define ROS_MAP_GENERATOR_SPACE_GENERATOR_H

#include <vector>
#include <list>
#include <algorithm>
#include <boost/graph/adjacency_list.hpp>

#include "room.h"

class RosNavigationEnvironment {
 public:
  using graph_t = boost::adjacency_list<boost::listS, boost::listS, boost::bidirectionalS> ;

  /**
   * Constructor of environment will randomly generate environment of parameters
   * @param amount amount of Rooms
   * @param min_size
   * @param max_size
   * @param coordinate
   * @param center
   * @param size
   */
  RosNavigationEnvironment(size_t amount,
                           int64_t min_size,
                           int64_t max_size,
                           int64_t coordinate,
                           int64_t center,
                           size_t size);

  const std::vector<Room> &rooms() const { return rooms_; };

  size_t width() const { return width_; }

  size_t height() const { return height_; }

 private:
  /**
   * separates overlapping rooms
   * @param padding allow rooms to overlap by `padding`
   */
  void separateRooms(int64_t padding = 1);

  /**
   * connect rooms and create graph of them
   */
  void connectRooms();

  /**
   * removes rooms that are overbound
   */
  void removeOverboundingRooms();

  /**
   * set of rooms
   */
  std::vector<Room> rooms_;
  std::vector<Room> halls_;
  std::vector<graph_t::vertex_descriptor> hall_vertices_;
  graph_t room_graph_;

  size_t width_;
  size_t height_;
};


#endif //ROS_MAP_GENERATOR_SPACE_GENERATOR_H
