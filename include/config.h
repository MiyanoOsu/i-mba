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
IMO, this non-standard ssize_t should not be used.
However, it's a good example of how to handle something like this.
*/


#if defined(__STDC_VERSION__) && __STDC_VERSION__>=199901L
#define STRING_REP_INT64  "%llu"
#define STRING_REP_UINT64 "%llu"
#define STRING_REP_ULONG  "%zu"
#else
#define STRING_REP_INT64  "%llu"
#define STRING_REP_UINT64 "%llu"
#define STRING_REP_ULONG  "%lu"
#endif

#endif
