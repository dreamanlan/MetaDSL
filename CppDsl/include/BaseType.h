#ifndef __BASETYPE_H__
#define __BASETYPE_H__

#ifndef __STDC_WANT_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#endif
#ifndef __STDC_WANT_SECURE_LIB__
#define __STDC_WANT_SECURE_LIB__ 1
#endif

#include <cassert>
#include <cstdint>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

#if defined(__WINDOWS__)

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <WinBase.h>

#elif defined(__LINUX__)
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <net/if.h>
#include <limits.h>

#endif

#if defined(__STDC_LIB_EXT1__) || defined(__STDC_SECURE_LIB__)
#else
#define strcpy_s(d,n,s) strcpy(d,s)
#endif

#ifndef TRUE
#define TRUE			1
#endif

#ifndef FALSE
#define FALSE			0
#endif

#ifndef INVALID_ID
#define INVALID_ID		-1
#endif

#ifndef INVALID_INDEX
#define INVALID_INDEX   -1
#endif

#ifndef INVALID_INDEX
#define INVALID_INDEX   -1
#endif

#ifndef MyAssert
#define MyAssert(x)
#endif

#endif //__BASETYPE_H__