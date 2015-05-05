#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>
#include <type_traits>
#include <SDL2/SDL.h>

class Random
{
public:
  template <typename T, typename EngineT = std::minstd_rand>
  static T Between(T min, T max, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0);
  template <typename T, typename EngineT = std::minstd_rand>
  static T Between(T min, T max, typename std::enable_if<std::is_integral<T>::value>::type * = 0);

  template <typename T, typename EngineT = std::minstd_rand>
  static T BetweenNormal(T min, T max, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0);
  template <typename T, typename EngineT = std::minstd_rand>
  static T BetweenNormal(T min, T max, typename std::enable_if<std::is_integral<T>::value>::type * = 0);

  template <typename T, typename EngineT = std::minstd_rand>
  static bool CheckChance(T chance, typename std::enable_if<std::is_integral<T>::value>::type * = 0);
  template <typename T, typename EngineT = std::minstd_rand>
  static bool CheckChance(T chance, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0);

private:
  static std::random_device _entropyGenerator;
};

#include "Random.inl"

#endif
