#include "types.h"

void*
memset(void *dst, int c, uint n)
{
  char *cdst = (char *) dst;
  int i;
  for(i = 0; i < n; i++){
    cdst[i] = c;
  }
  return dst;
}

int
memcmp(const void *v1, const void *v2, uint n)
{
  const uchar *s1, *s2;

  s1 = v1;
  s2 = v2;
  while(n-- > 0){
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }

  return 0;
}

void*
memmove(void *dst, const void *src, uint n)
{
  const char *s;
  char *d;

  if(n == 0)
    return dst;
  
  s = src;
  d = dst;
  if(s < d && s + n > d){
    s += n;
    d += n;
    while(n-- > 0)
      *--d = *--s;
  } else
    while(n-- > 0)
      *d++ = *s++;

  return dst;
}

// memcpy exists to placate GCC.  Use memmove.
void*
memcpy(void *dst, const void *src, uint n)
{
  return memmove(dst, src, n);
}

int
strncmp(const char *p, const char *q, uint n)
{
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

char*
strncpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  while(n-- > 0 && (*s++ = *t++) != 0)
    ;
  while(n-- > 0)
    *s++ = 0;
  return os;
}

// Like strncpy but guaranteed to NUL-terminate.
char*
safestrcpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  if(n <= 0)
    return os;
  while(--n > 0 && (*s++ = *t++) != 0)
    ;
  *s = 0;
  return os;
}

int
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

char*
strnindent(char *s, char *w, int indent) 
{ 
  int i ; 
  for (i = 0 ; s[i] ; i++) {
    w[i] = s[i] ;
  }
  for(; i < indent ; i++) { 
    w[i] = *(char *) " " ; 
  }
  w[i] = '\0' ; 
  return w ;
}

char *
strnreverse(char *s, int len)
{
  int start = 0;
  int end = len - 1;
  while (start < end) {
      char temp = s[start];
      s[start] = s[end];
      s[end] = temp;
      end--;
      start++;
  }
  return s ; 
}

char* 
stritoa(int num, char *s, int base)
{

    int i = 0;
    int isNegative = 0; 
 
    if (num == 0){
        s[i++] = '0';
        s[i] = '\0';
        return s;
    }
 
    if (num < 0 && base == 10){
        isNegative = 1;
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % base;
        s[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    if (isNegative)
        s[i++] = '-';
 
    s[i] = '\0'; 
    return strnreverse(s, i);
}

