#ifndef CONFIG_H__
#define CONFIG_H__

#define HORIZONTAL_CONTROLS 0
#define VERTICAL_CONTROLS 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int32_t fullscreen;
	/* For input remapping */
	uint32_t config_buttons[19];
	int32_t frameskip;
} t_config;
extern t_config option;

#ifdef __cplusplus
};
#endif


/*
Ordinarily we want to put #ifdef __cplusplus extern "C" in C library 
headers to enable them to get used by c++ sources.
However, we want to support building this library as C++ as well, so a
special technique is called for.
*/

#define BEGIN_DECLS
#define END_DECLS

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

#endif
