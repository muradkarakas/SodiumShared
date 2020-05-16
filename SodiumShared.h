#ifndef  _HTSQL_SHARED_H
#define _HTSQL_SHARED_H

#define SODIUM_SHARED_API				__declspec(dllexport)

#include "pch.h"

#include <io.h>
#include "base64.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "dllmain.h"

#define MAX_FORMULA_COLUMN_IMAGE_SIZE	10485760

typedef void * HANDLE;

	SODIUM_SHARED_API void		mkCoreDebug(const char *file, int line, const char *first, ...);
	SODIUM_SHARED_API char		* mkItoa(size_t value, char* result);
	SODIUM_SHARED_API void		mkFree(HANDLE pHeapHandle, void *ptr);
	SODIUM_SHARED_API void		* mkMalloc(HANDLE pHeapHandle, size_t memsize, const char *sourceFile, int sourceLine);
	SODIUM_SHARED_API void		mkFreeAdv(HANDLE pHeapHandle, void **ptr);
	SODIUM_SHARED_API void		* mkReAlloc(HANDLE pHeapHandle, void *ptr, size_t newmemsize);
	SODIUM_SHARED_API char		* mkStrcat(HANDLE pHeapHandle, const char *sourceFile, int sourceLine, const char * first, ...);
	SODIUM_SHARED_API wchar_t   * mkStrcatW(HANDLE pHeapHandle, const char* sourceFile, int sourceLine, const wchar_t* first, ...);
	SODIUM_SHARED_API char		* mkStrdup(HANDLE pHeapHandle, const char *sourceStr, const char *sourceFile, int sourceLine);
	SODIUM_SHARED_API wchar_t	* mkStrdupW(HANDLE pHeapHandle, const wchar_t *sourceStr, const char *sourceFile, int sourceLine);
	SODIUM_SHARED_API char		* mkStrdupN(HANDLE pHeapHandle, const char *sourceStr, int len, const char *sourceFile, int sourceLine);
	SODIUM_SHARED_API int		mkIsStringEmpty(const char *str);
	SODIUM_SHARED_API void		mkLowerCaseDriveLetterW(wchar_t* s);
	SODIUM_SHARED_API void		mkLowerCaseDriveLetterA(char* s);
	SODIUM_SHARED_API wchar_t*		GetFileName(wchar_t* path);

#endif // ! _HTSQL_SHARED_H

