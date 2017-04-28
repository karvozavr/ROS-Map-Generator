#include "space_generator.h"

void SpaceGenerator::separateRooms(int64_t padding) {

  // to hold any two rooms that are overlapping
  Room room_a;
  Room room_b;

  // holds delta values of the overlap
  int64_t delta_x;
  int64_t delta_x_a;
  int64_t delta_x_b;

  int64_t delta_y;
  int64_t delta_y_a;
  int64_t delta_y_b; // holds delta values of the overlap

  bool touching; // a boolean flag to keep track of touching rooms

  do {
    touching = false;

    for (size_t i = 0; i < rooms_.size(); i++) {
      room_a = rooms_.at(i);
      for (size_t j = i + 1; j < rooms_.size(); j++) { // for each pair of rooms
        room_b = rooms_.at(j);

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

SpaceGenerator::SpaceGenerator(size_t amount, int64_t size, int64_t coordinate) {
  for (int i = 0; i < amount; ++i) {
    rooms_.push_back(Room(rand() % coordinate + coordinate,
                          rand() % coordinate + coordinate,
                          rand() % size + size,
                          rand() % size + size
    ));
  }

  separateRooms();
}

std::vector<Room> &SpaceGenerator::rooms() {
  return rooms_;
}
