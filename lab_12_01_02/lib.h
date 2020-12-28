#ifndef __LIB_H__
#define __LIB_H__

#include <ctype.h>
#include <math.h>

#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif
#define ARR_DECL __cdecl

ARR_DLL void ARR_DECL shift(int *a, int n, int k);
ARR_DLL void ARR_DECL square_numbers(int *a, int n, int *b);

#endif