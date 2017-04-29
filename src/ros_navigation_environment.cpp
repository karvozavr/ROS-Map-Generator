#include "ros_navigation_environment.h"

RosNavigationEnvironment::RosNavigationEnvironment(size_t amount,
                                                   int64_t min_size,
                                                   int64_t max_size,
                                                   int64_t coordinate,
                                                   int64_t center,
                                                   size_t size)
    : width_(size), height_(size) {

  for (int i = 0; i < amount; ++i) {
    rooms_.push_back(Room(rand() % coordinate + center,
                          rand() % coordinate + center,
                          rand() % max_size + min_size,
                          rand() % max_size + min_size
    ));
  }

  separateRooms(0);
  removeOverboundingRooms();
}

void RosNavigationEnvironment::separateRooms(int64_t padding) {

  // holds delta values of the overlap
  int64_t delta_x;
  int64_t delta_x_a;
  int64_t delta_x_b;

  int64_t delta_y;
  int64_t delta_y_a;
  int64_t delta_y_b;

  // a bool flag to keep track of touching rooms
  bool touching;

  do {
    touching = false;

    for (size_t i = 0; i < rooms_.size(); i++) {
      Room &room_a = rooms_.at(i);
      for (size_t j = i + 1; j < rooms_.size(); j++) { // for each pair of rooms
        Room &room_b = rooms_.at(j);

        if (room_a.touches(room_b, padding)) { // if the two rooms touch (allowed to overlap by 1)
          touching = true; // update the touching flag so the loop iterates again

          // find the two smallest deltas required to stop the overlap
          delta_x = std::min(room_a.getRight() - room_b.getLeft() + padding,
                             room_a.getLeft() - room_b.getRight() - padding);
          delta_y = std::min(room_a.getBottom() - room_b.getTop() + padding,
                             room_a.getTop() - room_b.getBottom() - padding);

          // only keep the smalled delta
          if (std::abs(delta_x) < std::abs(delta_y)) {
            delta_y = 0;
          } else {
            delta_x = 0;
          }

          // create a delta for each rectangle as half the whole delta.
          delta_x_a = -delta_x / 2;
          delta_x_b = delta_x + delta_x_a;

          // same for y
          delta_y_a = -delta_y / 2;
          delta_y_b = delta_y + delta_y_a;

          // shift both rectangles
          room_a.relocate(delta_x_a, delta_y_a);
          room_b.relocate(delta_x_b, delta_y_b);
        }
      }
    }
  } while (touching); // loop until no rectangles are touching
}



void RosNavigationEnvironment::removeOverboundingRooms() {

}

void RosNavigationEnvironment::connectRooms() {
  // Rooms to check between
  Room a;
  Room b;
  Room c;

  size_t hall_size = rooms_.size() / 3;

  std::sort(rooms_.begin(), rooms_.end(), Room::CompareBySquare());

  halls_.resize(hall_size);
  hall_vertices_.resize(hall_size);
  std::copy_n(rooms_.begin(), hall_size, halls_.begin());

  for (int i = 0; i < halls_.size(); ++i) {
    hall_vertices_[i] = boost::add_vertex(room_graph_);
  }

  // squared distance between each of the 3 rooms
  double a_to_b_distance, a_to_c_distance, b_to_c_distance;

  bool skip;


  for (size_t i = 0; i < halls_.size(); i++) {
    a = halls_.at(i);
    for (size_t j = i + 1; j < halls_.size(); j++) { // for each pair of rooms
      skip = false;

      b = halls_.at(j);

      // get the squared distance between a and b
      a_to_b_distance = pow(a.getCenterX() - b.getCenterX(), 2) + pow(a.getCenterY() - b.getCenterY(), 2);
      for (size_t k = 0; k < halls_.size(); k++) { // loop through all other rooms
        // that are not a or b
        if (k == i || k == j) {
          continue;
        }

        c = halls_.at(k);

        // get the other two applicable distances
        a_to_c_distance = pow(a.getCenterX() - c.getCenterX(), 2) + pow(a.getCenterY() - c.getCenterY(), 2);
        b_to_c_distance = pow(b.getCenterX() - c.getCenterX(), 2) + pow(b.getCenterY() - c.getCenterY(), 2);

        /*
         * if the distance between a and c or b and c are smaller than a,
         * the pair (a, b) is not a graph edge
         */
        if (a_to_c_distance < a_to_b_distance && b_to_c_distance < a_to_b_distance) {
          skip = true;
        }

        // break the loop and go to the next (a, b) pair
        if (skip) {
          break;
        }
      }

      // if this (a, b) pair was never skipped, it should be an edge
      if (!skip) {
        boost::add_edge(hall_vertices_[i], hall_vertices_[j], room_graph_);
      }
    }
  }
}

