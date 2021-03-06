// __STM32_PROCESSOR__ needs to be defined to exclude certain headers.
#ifndef __ALLHEADERS_H__
#define __ALLHEADERS_H__
//=============================================================================
// Standard C11 
// https://en.wikipedia.org/wiki/C_standard_library click to get details
// http://www.schweikhardt.net/identifiers.html for a list of what is defined where
// http://www.open-std.org/jtc1/sc22/wg14/ official
// https://code-reference.com/c Reference for the C library
//=============================================================================
#include <assert.h> // Contains the assert macro, used to assist with detecting logical errors and other types of bug in debugging versions of a program.
#include <complex.h> // A set of functions for manipulating complex numbers.
#include <ctype.h> // Defines set of functions used to classify characters by their types or to convert between upper and lower case in a way that is independent of the used character set (typically ASCII or one of its extensions, although implementations utilizing EBCDIC are also known).
#include <errno.h> // For testing error codes reported by library functions.
#include <fenv.h> // Defines a set of functions for controlling floating-point environment.
#include <float.h> // Defines macro constants specifying the implementation-specific properties of the floating-point library.
#include <inttypes.h> // Defines exact width integer types.
#include <iso646.h> // Defines several macros that implement alternative ways to express several standard tokens. For programming in ISO 646 variant character sets.
#include <limits.h> // Defines macro constants specifying the implementation-specific properties of the integer types.
#include <locale.h> // Defines localization functions.
#include <math.h> // Defines common mathematical functions.
#include <setjmp.h> // Declares the macros setjmp and longjmp, which are used for non-local exits
#include <signal.h> // Defines signal handling functions.
#include <stdarg.h> // For accessing a varying number of arguments passed to functions.
#include <stdbool.h> // Defines a boolean data type.
#include <stddef.h> // Defines several useful types and macros.
#include <stdint.h> // Defines exact width integer types.
#include <stdio.h> // Defines core input and output functions
#include <stdlib.h> // Defines numeric conversion functions, pseudo-random numbers generation functions, memory allocation, process control functions
#include <string.h> // Defines string handling functions.
#include <tgmath.h> // Defines type-generic mathematical functions.
#include <time.h> // Defines date and time handling functions
#include <wchar.h> // Defines wide string handling functions.
#include <wctype.h> // Defines set of functions used to classify wide characters by their types or to convert between upper and lower case

#ifndef __STM32_PROCESSOR__ //This should work on other things.
#include <stdalign.h> // For querying and specifying the alignment of objects.
#include <stdatomic.h> // For atomic operations on data shared between threads.
#include <stdnoreturn.h> // For specifying non-returning functions.
#include <threads.h> // Defines functions for managing multiple Threads as well as mutexes and condition variables.
#include <uchar.h> // Types and functions for manipulating Unicode characters.
#endif //STM32

//=============================================================================
// Something else 
//=============================================================================

#endif // __ALLHEADERS_H__
