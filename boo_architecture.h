#ifndef BOO_ARCHITECTURE_H
#define BOO_ARCHITECTURE_H
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#if defined(_WIN64) || defined(WIN64) || defined(__IA64__) \
  || defined(__ia64__) || defined(_IA64) || defined(__amd64__) \
  || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
  #define BOO_x64_ARCH
#elif defined(_WIN32) || defined(WIN32) || defined(__i386__) \
  || defined(__i486__) || defined(__i586__) || defined(__i686__)
  #define BOO_x86_ARCH
#elif defined(__arm__)
  #define BOO_ARM_ARCH
#elif defined(__aarch64__)
  #define BOO_ARM64_ARCH
#elif defined(__SUNPRO_CC_COMPAT) || defined(__sun) || defined(__sun__)
  #define BOO_x64_ARCH
#else
#error "boo_architecture.h, cannot find architecture"
#endif
#endif
