#ifndef RANDOM_INLINE
#define RANDOM_INLINE

template <typename T, typename EngineT> T Random::Between(T min, T max, typename std::enable_if<std::is_floating_point<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_real_distribution<T> dist(min, max);
  return dist(engine);
}

template <typename T, typename EngineT> T Random::Between(T min, T max, typename std::enable_if<std::is_integral<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_int_distribution<T> dist(min, max);
  return dist(engine);
}

template <typename T, typename EngineT> T Random::BetweenNormal(T min, T max, typename std::enable_if<std::is_floating_point<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::normal_distribution<T> dist(min, max);
  return dist(engine);
}

template <typename T, typename EngineT> T Random::BetweenNormal(T min, T max, typename std::enable_if<std::is_integral<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_int_distribution<T> dist(min, max);
  //std::normal_distribution<double> dist(static_cast<double>(min), static_cast<double>(max));
  auto result1 = dist(engine);
  auto result2 = dist(engine);
  auto result = round((result1+result2)/2);
  return result;
}

template <typename T, typename EngineT> bool Random::CheckChance(T chance, typename std::enable_if<std::is_floating_point<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_real_distribution<T> dist(0, 100);
  return dist(engine) < chance;
}

template <typename T, typename EngineT> bool Random::CheckChance(T chance, typename std::enable_if<std::is_integral<T>::value>::type *)
{
  EngineT engine(_entropyGenerator());
  std::uniform_int_distribution<T> dist(0, 100);
  return dist(engine) < chance;
}

#endif
