#ifndef _COMMON_API_H
#define _COMMON_API_H

/*
Ordinarily we want to put #ifdef __cplusplus extern "C" in C library 
headers to enable them to get used by c++ sources.
However, we want to support building this library as C++ as well, so a
special technique is called for.
*/

#define RETRO_BEGIN_DECLS
#define RETRO_END_DECLS

#ifdef __cplusplus

#ifdef CXX_BUILD
/* build wants everything to be built as c++, so no extern "C" */
#else
#undef BEGIN_DECLS
#undef END_DECLS
#define BEGIN_DECLS extern "C" {
#define END_DECLS }
#endif

#else

/* header is included by a C source file, so no extern "C" */

#endif

/*
IMO, this non-standard ssize_t should not be used.
However, it's a good example of how to handle something like this.
*/
#ifdef _MSC_VER
#ifndef HAVE_SSIZE_T
#define HAVE_SSIZE_T
#if defined(_WIN64)
typedef __int64 ssize_t;
#elif defined(_WIN32)
typedef int ssize_t;
#endif
#endif
#elif defined(__MACH__)
#include <sys/types.h>
#endif

#ifdef _WIN32
#define STRING_REP_INT64  "%I64u"
#define STRING_REP_UINT64 "%I64u"
#define STRING_REP_ULONG  "%Iu"
#elif defined(__STDC_VERSION__) && __STDC_VERSION__>=199901L
#define STRING_REP_INT64  "%llu"
#define STRING_REP_UINT64 "%llu"
#define STRING_REP_ULONG  "%zu"
#else
#define STRING_REP_INT64  "%llu"
#define STRING_REP_UINT64 "%llu"
#define STRING_REP_ULONG  "%lu"
#endif

/*
I would like to see retro_inline.h moved in here; possibly boolean too.

rationale: these are used in public APIs, and it is easier to find problems
and write code that works the first time portably when theyre included uniformly
than to do the analysis from scratch each time you think you need it, for each feature.

Moreover it helps force you to make hard decisions: if you EVER bring in boolean.h,
then you should pay the price everywhere, so you can see how much grief it will cause.

Of course, another school of thought is that you should do as little damage as possible
in as few places as possible...
*/

#endif
