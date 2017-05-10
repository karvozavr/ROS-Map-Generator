/*
 * ROS map generator
 *  room.h
 *
 * Created by Dmitriy Abramov (karvozavr@gmail.com) April, 2017
 */

#ifndef ROS_MAP_GENERATOR_ROOM_H
#define ROS_MAP_GENERATOR_ROOM_H

#include <vector>
#include <cstdint>
#include <cassert>
#include "randomizer.h"

class Room {
 public:
  /**
   * basic room constructor
   * @param x
   * @param y y relative position
   * @param width width of room
   * @param height height of room
   */
  Room(int64_t x = 0, int64_t y = 0, int64_t width = 0, int64_t height = 0) :
      x_pos_(x),
      y_pos_(y),
      width_(width),
      height_(height) {
    assert(height >= 0);
  }

  /**
   * Room constructor for obstacles generation
   * @param random randomizer
   * @param corridor_width width of corridor
   * @param x x relative position
   * @param y y relative position
   * @param width width of room
   * @param height height of room
   */
  Room(Randomizer<int64_t> *random, int64_t corridor_width,
       int64_t x = 0, int64_t y = 0, int64_t width = 0, int64_t height = 0);

  int64_t getTop() const;
  int64_t getBottom() const;
  int64_t getLeft() const;
  int64_t getRight() const;
  int64_t getSquare() const;
  double getCenterX() const;
  double getCenterY() const;

  const std::vector<Room> &obstacles() const { return obstacles_; }

  /**
   * change room coordinates by
   * @param delta_x
   * @param delta_y
   */
  void relocate(int64_t delta_x, int64_t delta_y);

  /**
   * check, if this room intersects with other (allowed to intersect by padding)
   * @param other
   * @param padding
   * @return intersects with allowed padding -> true, else -> false
   */
  bool touches(const Room &other, int64_t padding) const;

  struct CompareBySquare {
    bool operator()(const Room &lhs, const Room &rhs) const;
  };

 private:
  int64_t x_pos_;
  int64_t y_pos_;

  int64_t width_;
  int64_t height_;

  std::vector<Room> obstacles_;
  Randomizer<int64_t> *random_;
};


#endif //ROS_MAP_GENERATOR_ROOM_H
