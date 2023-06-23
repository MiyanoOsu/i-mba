#ifndef _MEMALIGN_H
#define _MEMALIGN_H

#include <stddef.h>

#include <config.h>

BEGIN_DECLS

void *memalign_alloc(size_t boundary, size_t size);

void *memalign_alloc_aligned(size_t size);

void memalign_free(void *ptr);

END_DECLS

#endif
