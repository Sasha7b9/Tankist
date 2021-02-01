#pragma once

#define GL_GLEXT_LEGACY
#define GLX_GLXEXT_LEGACY
#define XK_MISCELLANY

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <dlfcn.h>
#include <cpuid.h>
#include <signal.h>
#include <errno.h>
#include <xmmintrin.h>
#include <GL/glx.h>
#include <X11/extensions/Xrandr.h>
#include <X11/keysymdef.h>
#include <X11/XKBlib.h>
#include <alsa/asoundlib.h>
#include <linux/joystick.h>
#include <math.h>
#include <new>

#undef Complex
