#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

typedef int (*unlinkat_type)(int, const char *, int);
 
int unlinkat(int dirfd, const char *pathname, int flags) {
  unlinkat_type orig_unlinkat = (unlinkat_type)dlsym(RTLD_NEXT, "unlinkat");
  if(strstr(pathname, "FIX")) {
    return EPERM;
  }
  return orig_unlinkat(dirfd, pathname,flags);
}