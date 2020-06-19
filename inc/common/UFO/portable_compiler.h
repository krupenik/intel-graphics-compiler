/*===================== begin_copyright_notice ==================================

Copyright (c) 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


======================= end_copyright_notice ==================================*/

#ifndef UFO_PORTABLE_COMPILER_H
#define UFO_PORTABLE_COMPILER_H

/*
 * This file provides mappings between MSVC and GCC compiler specific modifiers.
 * This file also provides portable definitions of some helper macros.
 */

#if defined(_MSC_VER)

    #define __attribute__(x)                __attribute___ x
    #define __attribute___(x)               __attribute___##x
    #define __attribute___aligned(y)        __declspec(align(y))
    #define __attribute___always_inline     __forceinline
    #define __attribute___deprecated        __declspec(deprecated)
    #define __attribute___noinline          __declspec(noinline)
    #define __attribute_____noinline__      __declspec(noinline)
    #define __attribute___nothrow           __declspec(nothrow)

    #define __thread                        __declspec(thread)
    #define __builtin_popcount              __popcnt

    #define __attr_unused

#elif defined(__clang__)

    #define __noop
    #define __fastcall
    #if defined __x86_64__
        #define __stdcall       // deprecated for x86-64
        #define __cdecl         // deprecated for x86-64
    #else
        #define __cdecl         __attribute__((__cdecl__))
        #define __stdcall       __attribute__((__stdcall__))
    #endif

    #define __declspec(x)           __declspec_##x
    #define __declspec_align(y)     __attribute__((aligned(y)))
    #define __declspec_deprecated   __attribute__((deprecated))
    #define __declspec_dllexport
    #define __declspec_dllimport
    #define __declspec_noinline     __attribute__((__noinline__))
    #define __declspec_nothrow      __attribute__((nothrow))
    #define __declspec_novtable
    #define __declspec_thread       __thread

    #define __forceinline       inline __attribute__((__always_inline__))

    // __debugbreak may be defined as builtin
    #if !__has_builtin(__debugbreak)
        #define __debugbreak()  do { asm volatile ("int3;"); } while (0)
    #endif
    #define __popcnt                __builtin_popcount

    #ifndef __attr_unused
        #define __attr_unused        __attribute__((unused))
    #endif

#elif __GNUC__

    #if __GNUC__ < 4
        #error "Unsupported GCC version. Please use 4.0+"
    #endif

    #define __noop
    #define __fastcall
    #if defined __x86_64__
        #define __stdcall       // deprecated for x86-64
        #define __cdecl         // deprecated for x86-64
    #else
        #define __cdecl         __attribute__((__cdecl__))
        #define __stdcall       __attribute__((__stdcall__))
    #endif

    #define __declspec(x)           __declspec_##x
    #define __declspec_align(y)     __attribute__((aligned(y)))
    #define __declspec_deprecated   __attribute__((deprecated))
    #define __declspec_dllexport
    #define __declspec_dllimport
    #define __declspec_noinline     __attribute__((__noinline__))
    #define __declspec_nothrow      __attribute__((nothrow))
    #define __declspec_novtable
    #define __declspec_thread       __thread

    #define __forceinline       inline __attribute__((__always_inline__))

    #define __debugbreak()      do { asm volatile ("int3;"); } while (0)
    #define __popcnt                __builtin_popcount

    #define __attr_unused            __attribute__((unused))

#else

    #pragma message "unknown compiler!"

#endif


/* compile-time ASSERT */

#ifndef C_ASSERT
    #define __CONCATING( a1, a2 )     a1 ## a2
    #define __UNIQUENAME( a1, a2 )  __CONCATING( a1, a2 )

    #define UNIQUENAME( __text )    __UNIQUENAME( __text, __COUNTER__ )

    #define C_ASSERT(e) typedef char UNIQUENAME(STATIC_ASSERT_)[(e)?1:-1]
#endif


#endif  // UFO_PORTABLE_COMPILER_H
