#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>
#include <type_traits>

class Random
{
public:
  template <typename T, typename EngineT = std::mt19937>
  static T Between(T min, T max, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0);
  template <typename T, typename EngineT = std::mt19937>
  static T Between(T min, T max, typename std::enable_if<std::is_integral<T>::value>::type * = 0);

  template <typename T, typename EngineT = std::mt19937>
  static bool CheckChance(T chance, typename std::enable_if<std::is_integral<T>::value>::type * = 0);
  template <typename T, typename EngineT = std::mt19937>
  static bool CheckChance(T chance, typename std::enable_if<std::is_floating_point<T>::value>::type * = 0);
private:
  static std::random_device _entropyGenerator;  
};

#include "Random.inl"

#endif
