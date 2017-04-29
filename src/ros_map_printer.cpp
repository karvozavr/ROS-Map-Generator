#include "ros_map_printer.h"
#include "costmap_2d/costmap_2d.h"
void RosNavigationEnvironmentRenderer::render() {

  costmap_2d::Costmap2D map();
  for (const Room &room : environment_.rooms()) {
    for (int64_t x = room.getLeft(); x < room.getRight(); ++x) {
      for (int64_t y = room.getBottom(); y < room.getTop(); ++y) {
        space[x][y] = 255;
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
  out_stream_ << "P2" << '\n';
  out_stream_ << environment_.width() << ' ' << environment_.height() << '\n' << "255" << '\n';

  for (int64_t x = 0; x < environment_.width(); ++x) {
    for (int64_t y = 0; y < environment_.height(); ++y) {
      out_stream_ << static_cast<int>(space[x][y]) << ' ';
    }

    out_stream_ << std::endl;
  }
}
