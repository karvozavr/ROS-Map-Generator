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

double Room::getCenterX() const {
  return (getLeft() + getRight()) / 2.0;
}

double Room::getCenterY() const {
  return (getBottom() + getTop()) / 2.0;
}


Room::Room(Randomizer<int64_t> *random, int64_t corridor_width, int64_t x, int64_t y, int64_t width, int64_t height)
    : x_pos_(x),
      y_pos_(y),
      width_(width),
      height_(height),
      random_(random) {

  if (corridor_width != 0) {
    if (height_ > 2 * corridor_width && width > 2 * corridor_width) {
      for (int i = 0; i < std::min(width_, height_) / corridor_width; ++i) {
        int64_t kek1 = std::abs(random_->next_rand()) % corridor_width + corridor_width;
        int64_t   kek2 = std::abs(random_->next_rand()) % corridor_width + corridor_width;
        obstacles_.push_back(Room(std::abs(random_->next_rand()) % width_,
                                  std::abs(random_->next_rand()) % height_,
                                  kek1,
                                  kek2
        ));
      }

      for (auto obstacle = obstacles_.begin(); obstacle != obstacles_.end(); ++obstacle) {
        if (obstacle->getTop() >= height_ - corridor_width ||
            obstacle->getBottom() < 0 + corridor_width||
            obstacle->getRight() >= width_ - corridor_width ||
            obstacle->getLeft() < 0 + corridor_width) {
          obstacles_.erase(obstacle--);
        }
      }
    }
  }
}

bool Room::CompareBySquare::operator()(const Room &lhs, const Room &rhs) const {
  return lhs.getSquare() < rhs.getSquare();
}
