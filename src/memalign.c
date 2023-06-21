#include <stdint.h>
#include <stdlib.h>

#include <memalign.h>


void *memalign_alloc(size_t boundary, size_t size)
{
   void *ptr  = (void*)malloc(boundary + size + sizeof(uintptr_t));
   if (!ptr) return NULL;

   uintptr_t addr = ((uintptr_t)ptr + sizeof(uintptr_t) + boundary) & ~(boundary - 1);
   void **place   = (void**)addr;
   place[-1]      = ptr;

   return (void*)addr;
}

void memalign_free(void *ptr)
{
   if (!ptr) return;
   void ** p = (void**)ptr;
   free(p[-1]);
}

void *memalign_alloc_aligned(size_t size)
{
#if defined(__x86_64__) || defined(__LP64) || defined(__IA64__) || defined(_M_X64) || defined(_WIN64)
   return memalign_alloc(64, size);
#elif defined(__i386__) || defined(__i486__) || defined(__i686__) || defined(GEKKO)
   return memalign_alloc(32, size);
#else
   return memalign_alloc(32, size);
#endif
}