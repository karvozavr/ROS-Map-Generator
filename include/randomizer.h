//
// Created by karvozavr on 30/04/17.
//

#ifndef ROS_MAP_GENERATOR_RANDOMIZER_H
#define ROS_MAP_GENERATOR_RANDOMIZER_H


#include <iomanip>
#include <chrono>
#include <random>

template<typename T, typename distribution_type = std::normal_distribution<float>>
class Randomizer {
 public:
  /**
   * Randomizer basic constructor
   * @param seed seed for pseudo-random number generation
   */
  Randomizer(int64_t seed = std::chrono::system_clock::now().time_since_epoch().count())
      : seed_(seed),
        random_generator_(seed),
        distribution_(distribution_type(INT64_MAX / 2, INT64_MAX / 32)) {}

  /**
   * get random number
   * @return generated random number
   */
  T next_rand();

 private:
  int64_t seed_;
  std::mt19937 random_generator_;
  distribution_type distribution_;
};

template<typename T, typename distribution_type>
T Randomizer<T, distribution_type>::next_rand() {
  T val = static_cast<T>(distribution_(random_generator_)) + 2;
  return val;
}


#endif //ROS_MAP_GENERATOR_RANDOMIZER_H
