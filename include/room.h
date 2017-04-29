#ifndef ROS_MAP_GENERATOR_ROOM_H
#define ROS_MAP_GENERATOR_ROOM_H

#include <zconf.h>

class Room {
 public:
  Room(int64_t x = 0, int64_t y = 0, int64_t width = 0, int64_t height = 0)
      : x_pos_(x),
        y_pos_(y),
        width_(width),
        height_(height),
        id_(static_cast<size_t>(this)){}

  int64_t getTop() const;
  int64_t getBottom() const;
  int64_t getLeft() const;
  int64_t getRight() const;
  int64_t getSquare() const;
  double getCenterX() const;
  double getCenterY() const;
  size_t id() const;

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
  size_t id_;

  int64_t x_pos_;
  int64_t y_pos_;

  int64_t width_;
  int64_t height_;
};


#endif //ROS_MAP_GENERATOR_ROOM_H
