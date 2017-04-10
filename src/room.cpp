#include "room.h"

int64_t Room::getTop() const {
  return y_pos_ + height_;
}

int64_t Room::getBottom() const {
  return y_pos_;
}

int64_t Room::getLeft() const {
  return x_pos_;
}

int64_t Room::getRight() const {
  return x_pos_ + width_;
}

int64_t Room::getSquare() const {
  return width_ * height_;
}

void Room::relocate(int64_t delta_x, int64_t delta_y) {
  x_pos_ += delta_x;
  y_pos_ += delta_y;
}

bool Room::touches(const Room &other, int64_t padding) const {
  return getLeft() + padding < other.getRight() &&
         getRight() - padding > other.getLeft() &&
         getBottom() + padding < other.getTop() &&
         getTop() - padding > other.getBottom();
}

bool Room::CompareBySquare::operator()(const Room &lhs, const Room &rhs) const {
  return lhs.getSquare() < rhs.getSquare();
}

bool Room::CompareByX::operator()(const Room &lhs, const Room &rhs) const {
  return lhs.x_pos_ < rhs.x_pos_;
}

bool Room::CompareByY::operator()(const Room &lhs, const Room &rhs) const {
  return lhs.y_pos_ < rhs.y_pos_;
}
