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
        space[x][y] = 255;
      }
    }

    for (const Room &obstacle : room.obstacles()) {
      for (int64_t x = obstacle.getLeft(); x < obstacle.getRight(); ++x) {
        for (int64_t y = obstacle.getBottom(); y < obstacle.getTop(); ++y) {
          space[x + room.getLeft()][y + room.getBottom()] = 0;
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
              space[x + k][y + l] == 255) {
            flag = false;
          }
        }
      }

      if (flag && space[x][y] == 0) {
        space[x][y] = 204;
      }
    }
  }
}

void RosNavigationEnvironmentRenderer::save_to_pgm() {
  render();

  out_stream_ << "P5" << '\n';
  out_stream_ << environment_.width() << ' ' << environment_.height() << '\n' << "255" << '\n';

  for (int64_t y = 0; y < environment_.height(); ++y) {
    for (int64_t x = 0; x < environment_.width(); ++x) {
      out_stream_.write(reinterpret_cast<char*>(&(space[x][environment_.height() - y])), sizeof(uint8_t));
    }
  }
}
