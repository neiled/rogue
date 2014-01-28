/**************************************************************************
  NetZen :  Network Sensitivity Analysis and Visualization
                             -------------------
    copyright            : (C) 2009 by Carlos D. Correa
    email                : correac@cs.ucdavis.edu
***************************************************************************/
#ifndef TIMING_H
#define TIMING_H

#ifdef WIN32

# include <limits.h>
# include <windows.h>
# define usleep(x) Sleep((x)/1000)
  // Handling of timestamps and determination of time intervals
  struct timestamp { LARGE_INTEGER t; };
  static inline float LI2f(const LARGE_INTEGER &li)
  {
	// Workaround for MSVC compiler bug.  Sigh.
	float f = unsigned(li.HighPart) >> 16;  f *= 65536.0f;
	f += unsigned(li.HighPart) & 0xffff;    f *= 65536.0f;
	f += unsigned(li.LowPart) >> 16;        f *= 65536.0f;
	f += unsigned(li.LowPart) & 0xffff;
	return f;
  }
  static inline float operator - (const timestamp &t1, const timestamp &t2)
  {
	static LARGE_INTEGER PerformanceFrequency;
	static int status = QueryPerformanceFrequency(&PerformanceFrequency);
	if (status == 0) return 1.0f;
	return (LI2f(t1.t) - LI2f(t2.t)) / LI2f(PerformanceFrequency);
  }
  static inline timestamp now()
  {
	timestamp t;
	QueryPerformanceCounter(&t.t);
	return t;
  }

#else

# include <sys/time.h>
# include <unistd.h>
  typedef struct timeval timestamp;
  static inline float operator - (const timestamp &t1, const timestamp &t2)
  {
	return (float)(t1.tv_sec  - t2.tv_sec) +
	       1.0e-6f*(t1.tv_usec - t2.tv_usec);
  }
  static inline timestamp now()
  {
	timestamp t;
	gettimeofday(&t, NULL);
	return t;
  }

#endif

#endif
