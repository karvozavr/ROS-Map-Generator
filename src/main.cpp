#include <iostream>
#include "ros_navigation_environment.h"
#include "ros_map_printer.h"
#include <vector>
#include <ctime>
#include <fstream>

int main(int argc, char *argv[]) {

  srand(time(NULL));
  RosNavigationEnvironment nav_space(100, 60, 300, 80, 2500, 5000);

  std::ofstream out_stream;
  out_stream.open("saved.pgm");

  RosNavigationEnvironmentRenderer renderer(out_stream, nav_space);
  renderer.render();
  renderer.save_to_pgm();

  /*size_t size = 2048;
  std::vector<std::vector<int>> space(size + 1000, std::vector<int>(size + 1000, 0));

  for (Room &room : nav_space.rooms()) {
    for (int64_t i = room.getLeft(); i < room.getRight(); ++i) {
      for (int64_t j = room.getBottom(); j < room.getTop(); ++j) {
        space[i][j] = 255;
      }
    }
  }

  for (int64_t i = 0; i < size; ++i) {
    for (int64_t j = 0; j < size; ++j) {
      bool flag = true;
      for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
          if (i != 0 && j != 0 && space[i + k][j + l] == 255) {
            flag = false;
          }
        }
      }
      if (flag && space[i][j] == 0) {
        space[i][j] = 204;
      }
    }
  }*/



  return 0;
}