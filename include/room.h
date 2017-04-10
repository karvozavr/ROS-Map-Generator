#ifndef ROS_MAP_GENERATOR_ROOM_H
#define ROS_MAP_GENERATOR_ROOM_H


#include <zconf.h>

class Room {
 public:
  int64_t getTop() const;
  int64_t getBottom() const;
  int64_t getLeft() const;
  int64_t getRight() const;
  int64_t getSquare() const;

  void relocate(int64_t delta_x, int64_t delta_y);

  bool touches(const Room &other, int64_t padding) const;

  class CompareBySquare {
    bool operator()(const Room &lhs, const Room &rhs) const;
  };

  class CompareByX {
    bool operator()(const Room &lhs, const Room &rhs) const;
  };

  class CompareByY {
    bool operator()(const Room &lhs, const Room &rhs) const;
  };

 private:
  int64_t x_pos_;
  int64_t y_pos_;

  int64_t width_;
  int64_t height_;
};


#endif //ROS_MAP_GENERATOR_ROOM_H
