#define memcpy(dest, src, len) ((__ssp_bos0 (dest) != (size_t) -1) ? \
__builtin___memcpy_chk (dest, src, len, __ssp_bos0 (dest)) :\
__memcpy_ichk (dest, src, len))

static inline __attribute__((__always_inline__)) void *__memcpy_ichk (void *__restrict__ __dest, const void *__restrict__ __src, size_t __len){
  return __builtin___memcpy_chk (__dest, __src, __len, __ssp_bos0 (__dest));
}