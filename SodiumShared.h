/**
 * This file is part of Sodium Language project
 *
 * Copyright © 2020 Murad Karakaþ <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */

#pragma once

#if  defined(_SODIUM_SHARED)
	#define SODIUM_SHARED_API				__declspec(dllexport)
#else
	#define SODIUM_SHARED_API				__declspec(dllimport)
#endif


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


