/*
 * ROS map generator
 *  randomizer.h
 *
 * Created by Dmitriy Abramov (karvozavr@gmail.com) April, 2017
 */

#ifndef ROS_MAP_GENERATOR_RANDOMIZER_H
#define ROS_MAP_GENERATOR_RANDOMIZER_H


#include <iomanip>
#include <chrono>
#include <random>

template<typename T>
class Randomizer {
 public:
  /**
   * Randomizer basic constructor
   * @param seed seed for pseudo-random number generation
   */
  Randomizer(int64_t seed = std::chrono::system_clock::now().time_since_epoch().count())
      : seed_(seed),
        random_generator_(seed) {}

  /**
   * get random number
   * @return generated random number
   */
  T next_rand();

 private:
  int64_t seed_;
  std::mt19937 random_generator_;
};

template<typename T>
T Randomizer<T>::next_rand() {
  T val = static_cast<T>(random_generator_()) + 2;
  return val;
}


#endif //ROS_MAP_GENERATOR_RANDOMIZER_H
