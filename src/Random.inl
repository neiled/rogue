#ifndef RANDOM_INLINE
#define RANDOM_INLINE

template <typename T, typename EngineT>
T Random::Between(T min, T max, typename
  std::enable_if<std::is_floating_point<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_real_distribution<T> dist(min, max);
  return dist(engine);
}

template <typename T, typename EngineT>
T Random::Between(T min, T max, typename
  std::enable_if<std::is_integral<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_int_distribution<T> dist(min, max);
  return dist(engine);
}

#endif
