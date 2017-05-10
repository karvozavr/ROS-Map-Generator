/*
 * ROS map generator
 *  ros_navigation_environment_renderer.cpp
 *
 * Created by Dmitriy Abramov (karvozavr@gmail.com) April, 2017
 */

#include "ros_navigation_environment_renderer.h"

void RosNavigationEnvironmentRenderer::render() {

  for (const Room &room : environment_.rooms()) {
    if (room.getTop() >= environment_.height() ||
        room.getBottom() < 0 ||
        room.getRight() >= environment_.width() ||
        room.getLeft() < 0) {
      continue;
    }

    for (int64_t x = room.getLeft(); x < room.getRight(); ++x) {
      for (int64_t y = room.getBottom(); y < room.getTop(); ++y) {
        space[x][y] = Color::white;
      }
    }

    for (const Room &obstacle : room.obstacles()) {
      for (int64_t x = obstacle.getLeft(); x < obstacle.getRight(); ++x) {
        for (int64_t y = obstacle.getBottom(); y < obstacle.getTop(); ++y) {
          space[x + room.getLeft()][y + room.getBottom()] = Color::black;
        }
      }
    }
  }

  for (int64_t x = 0; x < environment_.width(); ++x) {
    for (int64_t y = 0; y < environment_.height(); ++y) {
      bool flag = true;
      for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
          if (x != 0 && y != 0 &&
              x < environment_.width() - 1 &&
              y < environment_.height() - 1 &&
              space[x + k][y + l] == Color::white) {
            flag = false;
          }
        }
      }

      if (flag && space[x][y] == 0) {
        space[x][y] = Color::gray;
      }
    }
  }
}

void RosNavigationEnvironmentRenderer::save_to_pgm() {
  render();

  int64_t min_x = INT64_MAX;
  int64_t max_x = 0;
  int64_t min_y = INT64_MAX;
  int64_t max_y = 0;

  for (const Room &room : environment_.rooms()) {
    min_x = std::min(min_x, room.getLeft());
    min_y = std::min(min_y, room.getBottom());

    max_x = std::max(max_x, room.getRight());
    max_y = std::max(max_y, room.getTop());
  }

  ++max_x;
  ++max_y;

  if (min_x > 0) {
    --min_x;
  }

  if (min_y > 0) {
    --min_y;
  }

  out_stream_ << "P5" << '\n';
  out_stream_ << max_x - min_x << ' ' << max_y - min_y << '\n' << "255" << '\n';

  for (int64_t y = min_y; y < max_y; ++y) {
    for (int64_t x = min_x; x < max_x; ++x) {
      out_stream_.write(reinterpret_cast<char *>(&(space[x][y])), sizeof(uint8_t));
    }
  }
}
