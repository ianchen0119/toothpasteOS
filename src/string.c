#include "string.h"

int strcmp(char *s, char *d){
  while(*s != '\0' && *s != '\0'){
    if(*s != *d) return -1;
  }
  if(*s != '\0' || *d != '\0'){
    return -1;
  }
  return 0;
}

void *memset(void *dst, int c, unsigned int n){
  char *cdst = (char *)dst;
  int i;
  for(i = 0; i < n; i++){
    cdst[i] = c;
  }
  return dst;
}

void *memcpy(void *dst, const void *src, unsigned int n){
  return memmove(dst, src, n);
}

void *memmove(void *dst, const void *src, unsigned int n){
  const char *s;
  char *d;

  s = src;
  d = dst;
  if(s < d && s + n > d){
    s += n;
    d += n;
    while(n-- > 0)
      *--d = *--s;
  }
  else
    while(n-- > 0)
      *d++ = *s++;

  return dst;
}