/*
 * platform_discovery.h - port/platform specific discovery macros.
 *
 * Written by
 *  Marco van den Heuvel <blackystardust68@yahoo.com>
 *
 * This file is part of VICE, the Versatile Commodore Emulator.
 * See README for copyright notice.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307  USA.
 *
 */

#ifndef VICE_PLATFORM_DISCOVERY_H
#define VICE_PLATFORM_DISCOVERY_H

#include "vice.h"

#include "uiapi.h"

#if !defined(WIN32_COMPILE) && defined(__CYGWIN32__)
#include <cygwin/version.h>
#endif

#undef XQUOTE
#undef QUOTE
#define QUOTE(x) XQUOTE(x)
#define XQUOTE(x) #x

/* Set compiler version */
#if (_MSC_VER == 1100)
#define PLATFORM_COMPILER "msvc5/vs97"
#endif

#if (_MSC_VER == 1200)
#define PLATFORM_COMPILER "msvc6/vs98"
#endif

#if (_MSC_VER == 1300)
#define PLATFORM_COMPILER "msvc7.0/vs2002"
#endif

#if (_MSC_VER == 1310)
#define PLATFORM_COMPILER "msvc7.1/vs2003"
#endif

#if (_MSC_VER == 1400)
#define PLATFORM_COMPILER "msvc8/vs2005"
#endif

#if (_MSC_VER == 1500)
#define PLATFORM_COMPILER "msvc9/vs2008"
#endif

#if (_MSC_VER == 1600)
#define PLATFORM_COMPILER "msvc10/vs2010"
#endif

#if (_MSC_VER == 1700)
#define PLATFORM_COMPILER "msvc11/vs2012"
#endif

#ifndef PLATFORM_COMPILER
#define PLATFORM_COMPILER "msvc"
#endif

/* win32/64 discovery */
#ifdef WIN32_COMPILE
#  ifdef _WIN64
#    ifdef _M_IA64
#      ifndef PLATFORM_CPU
#        define PLATFORM_CPU "IA64"
#      endif
#    else
#      ifndef PLATFORM_CPU
#        define PLATFORM_CPU "X64"
#      endif
#    endif
#    ifndef PLATFORM_OS
#      define PLATFORM_OS "WIN64"
#    endif
#    ifndef PLATFORM_COMPILER
#      define PLATFORM_COMPILER "MSVC"
#    endif
#  else
#    ifdef WINMIPS
#      define PLATFORM_CPU "MIPS"
#      define PLATFORM_OS "WIN32"
#      ifndef PLATFORM_COMPILER
#        define PLATFORM_COMPILER "MSVC"
#      endif
#    else
#      ifndef __GNUC__
#        ifdef MSVC_RC
#          ifdef WATCOM_COMPILE
#            ifndef PLATFORM_COMPILER
#              define PLATFORM_COMPILER "WATCOM"
#            endif
#          else
#            ifndef PLATFORM_COMPILER
#              define PLATFORM_COMPILER "MSVC"
#            endif
#          endif
#        endif
#      endif
#      ifndef PLATFORM_OS
#        define PLATFORM_OS "WIN32"
#      endif
#      define FIND_X86_CPU
#    endif
#  endif
#endif

/* Cygwin discovery */
#if !defined(WIN32_COMPILE) && defined(__CYGWIN32__)
#  define PLATFORM_OS "Cygwin API " QUOTE(CYGWIN_VERSION_API_MAJOR) "." QUOTE(CYGWIN_VERSION_API_MINOR)
#  define FIND_X86_CPU
#endif


/* Interix/SFU/SUA discovery */
#ifdef __INTERIX
#  include <interix/registry.h>
#  include <interix/interix.h>
#  ifndef ROOT_KEY_SYSWOW
#    ifndef PTHREAD_CHUNK_SIZE
#      define PLATFORM_OS "Interix 3.0"
#    else
#      define PLATFORM_OS "Interix 3.5"
#    endif
#  else
#    ifndef REGVAL_ENABLE_SU_TO_ROOT
#      define PLATFORM_OS "Interix 5.2"
#    else
#      define PLATFORM_OS "Interix 6.x"
#    endif
#  endif
#  define FIND_X86_CPU
#endif

/* MacOS X discovery */
#ifdef __APPLE__
#  include "platform_macosx.h"
#endif


/* AIX discovery */

#ifdef _AIX
#  include "platform_aix_version.h"
#endif


/* AmigaOS 3.x discovery */
#ifdef AMIGA_M68K
#  define PLATFORM_OS "AmigaOS 3.x"
#endif


/* AmigaOS 4.x discovery */
#ifdef AMIGA_OS4
#  define PLATFORM_OS "AmigaOS 4.x"
#  define PLATFORM_CPU "PPC"
#endif


/* AROS discovery */
#ifdef AMIGA_AROS
#  define PLATFORM_OS "AROS"
#endif


/* MorphOS discovery */
#ifdef AMIGA_MORPHOS
#  define PLATFORM_OS "MorphOS"
#endif


/* Android discovery */
#ifdef __ANDROID__
#  define PLATFORM_OS "Android"
#endif


/* BeOS discovery */
#ifdef __BEOS__
#  ifdef WORDS_BIGENDIAN
#    define PLATFORM_CPU "PPC"
#    define PLATFORM_COMPILER "MetroWerks"
#  else
#    define FIND_X86_CPU
#  endif
#  define PLATFORM_OS "BeOS"
#endif /* __BEOS__ */

/* Haiku discovery */
#ifdef __HAIKU__
#  define PLATFORM_OS "Haiku"
#  define FIND_X86_CPU
#endif


/* BSDI discovery */
#ifdef __bsdi__
#  define PLATFORM_OS "BSDi"
#  define FIND_X86_CPU
#endif


/* DragonFly BSD discovery */
#ifdef __DragonFly__
#  define PLATFORM_OS "DragonFly BSD"
#  define FIND_X86_CPU
#endif


/* FreeBSD discovery */
#ifdef __FreeBSD__
#  include "platform_freebsd_version.h"
#endif


/* NetBSD discovery */
#ifdef __NetBSD__
#  include "platform_netbsd_version.h"
#endif


/* OpenBSD discovery */
#ifdef __OpenBSD__
#  include "platform_openbsd_version.h"
#endif


/* QNX 4.x discovery */
#if defined(__QNX__) && !defined(__QNXNTO__)
#  define PLATFORM_OS "QNX 4.x"
#  define PLATFORM_COMPILER "Watcom"
#  define FIND_X86_CPU
#endif


/* QNX 6.x discovery */
#ifdef __QNXNTO__
#  include "platform_qnx6_version.h"
#  ifdef __arm__
#    define PLATFORM_CPU "ARMLE"
#  endif
#  ifdef __mips__
#    define PLATFORM_CPU "MIPSLE"
#  endif
#  ifdef __sh__
#    define PLATFORM_CPU "SHLE"
#  endif
#  if defined(__powerpc__) || defined(__ppc__)
#    define PLATFORM_CPU "PPCBE"
#  endif
#  ifndef PLATFORM_CPU
#    define FIND_X86_CPU
#  endif
#endif


/* HPUX discovery */
#if defined(__hpux) || defined(_hpux)
#  define PLATFORM_OS "HPUX"
#endif


/* IRIX discovery */
#ifdef __sgi
#  define PLATFORM_OS "IRIX"
#endif


/* OpenServer 5.x discovery */
#ifdef OPENSERVER5_COMPILE
#  define PLATFORM_OS "OpenServer 5.x"
#  define FIND_X86_CPU
#endif


/* OpenServer 6.x discovery */
#ifdef OPENSERVER6_COMPILE
#  define PLATFORM_OS "OpenServer 6.x"
#  define FIND_X86_CPU
#endif


/* UnixWare 7.x discovery */
#ifdef _UNIXWARE7
#  define PLATFORM_OS "UnixWare 7.x"
#  define FIND_X86_CPU
#endif


/* SunOS and Solaris discovery */
#if defined(sun) || defined(__sun)
#  if defined(__SVR4) || defined(__svr4__)
#    define PLATFORM_OS "Solaris"
#  else
#    define PLATFORM_OS "SunOS"
#  endif
#endif


/* UWIN discovery */
#ifdef _UWIN
#  define PLATFORM_OS "UWIN"
#  define FIND_X86_CPU
#endif


/* Linux discovery */
#ifdef __linux
#  include "platform_linux_libc_version.h"
#endif


/* DYNIX discovery */
#ifdef _SEQUENT_
#  define PLATFORM_OS "DYNIX"
#endif


/* GNU Hurd discovery */
#ifdef __GNU__
#  define PLATFORM_OS "GNU Hurd"
#endif


/* LynxOS discovery */
#ifdef __Lynx__
#  define PLATFORM_OS "LynxOS"
#endif


/* Minix discovery */
#ifdef __minix
#  define PLATFORM_OS "Minix"
#endif


/* DOS discovery */
#ifdef __DOS__
#  define PLATFORM_OS "DOS"
#endif


/* OS/2 discovery */
#ifdef __OS2__
#  define PLATFORM_OS "OS/2"
#endif


/* Sinux (Reliant UNIX) discovery */
#ifdef sinux
#  define PLATFORM_OS "Sinux"
#endif


/* Symbian OS discovery */
#ifdef __SYMBIAN32__
#  define PLATFORM_OS "Symbian OS"
#endif


/* Tru64 discovery */
#if defined(__osf__) || defined(__osf)
#  define PLATFORM_OS "Tru64"
#endif


/* Ultrix discovery */
#if defined(ultrix) || defined(__ultrix) || defined(__ultrix)
#  define PLATFORM_OS "Ultrix"
#endif


/* VMS discovery */
#if defined(VMS) || defined(__VMS)
#  define PLATFORM_OS "VMS"
#endif


/* XBOX(360) discovery */
#ifdef _XBOX
#  ifdef _XBOX_VER
#    if (_XBOX_VER>199)
#      define PLATFORM_OS "XBOX360"
#    else
#      define PLATFORM_OS "XBOX"
#    endif
#  endif
#endif


/* vxworks discovery */
#ifdef __vxworks__
#  define PLATFORM_OS "VXWORKS"
#endif


/* Generic cpu discovery */
#include "platform_cpu_type.h"

/* Generic compiler discovery */
#include "platform_compiler.h"

/* Fallbacks for unidentified systems */
#ifndef PLATFORM_CPU
#  define PLATFORM_CPU "unknown CPU"
#endif

#ifndef PLATFORM_OS
#  define PLATFORM_OS "unknown OS"
#endif

#ifndef PLATFORM_COMPILER
#  define PLATFORM_COMPILER "unknown compiler"
#endif

#endif
