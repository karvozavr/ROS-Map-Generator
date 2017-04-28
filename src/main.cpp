#include <iostream>
#include "space_generator.h"
#include <vector>

int main(int argc, char *argv[]) {

  srand(1337);
  SpaceGenerator generator(7, 7, 7);

  size_t size = 40;
  std::vector<std::vector<int>> space(size, std::vector<int>(size, 0));

  for (Room &room : generator.rooms()) {
    for (int64_t i = room.getLeft(); i < room.getRight(); ++i) {
      for (int64_t j = room.getBottom(); j < room.getTop(); ++j) {
        space[i][j] = 1;
      }
    }
  }

  for (int64_t i = 0; i < size; ++i) {
    for (int64_t j = 0; j < size; ++j) {
      std::cout << space[i][j];
    }

    std::cout << std::endl;
  }
  std::cout << "Hi";

  return 0;
}