#include "pch.h"

#include "SodiumShared.h"

extern CRITICAL_SECTION                htsqlCriticalSection;
 
// Returns filename portion of the given path
// Returns empty string if path is directory
SODIUM_SHARED_API wchar_t*
GetFileName(
	wchar_t* path
)
{
	wchar_t* filename = wcsrchr(path, L'\\');
	if (filename == NULL)
		filename = path;
	else
		filename++;
	return filename;
}

SODIUM_SHARED_API void
mkLowerCaseDriveLetterW(
	wchar_t *fileUri
) 
{
	if (fileUri[1] == L':') {
		if (fileUri[0] == L'C')
			fileUri[0] = L'c';
		if (fileUri[0] == L'D')
			fileUri[0] = L'd';
		if (fileUri[0] == L'E')
			fileUri[0] = L'e';
		if (fileUri[0] == L'F')
			fileUri[0] = L'f';
	}
}

SODIUM_SHARED_API void
mkLowerCaseDriveLetterA(
	char* fileUri
	)
{
	if (fileUri[1] == ':') {
		if (fileUri[0] == 'C')
			fileUri[0] = 'c';
		if (fileUri[0] == 'D')
			fileUri[0] = 'd';
		if (fileUri[0] == 'E')
			fileUri[0] = 'e';
		if (fileUri[0] == 'F')
			fileUri[0] = 'f';
	}
}

SODIUM_SHARED_API int mkIsStringEmpty(const char *s) {
	while (*s != '\0') {
		if (!isspace((unsigned char)*s))
			return FALSE;
		s++;
	}
	return TRUE;
}

SODIUM_SHARED_API void mkCoreDebug(const char *file, int line, const char *first, ...)
 {
	va_list vl;
	HANDLE				hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

	//
	// saving current color information
	//
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;

	SetConsoleTextAttribute(hConsole, 4);

	const char *str = first;
	va_start(vl, first);
	while (str && str[0] != '\0') {
		wprintf(L"%hs", str);
		str = va_arg(vl, char*);
	}

	//
	// restoring the original colors
	//
	SetConsoleTextAttribute(hConsole, wOldColorAttrs);
}

/** \brief Convert int to char *
*
* \param value int
* \param result char*
* \return char*
*
*  Result will be put into result variable. size of the result variable should have enough to accommodate.
*  No memory allocation is made in the mkItoa function.
*/
SODIUM_SHARED_API char* mkItoa(size_t value, char* result) {

	int base = 10;

	// check that the base if valid
	if (base < 2 || base > 36) { *result = '\0'; return result; }

	char* ptr = result, *ptr1 = result, tmp_char;
	size_t tmp_value;

	do {
		tmp_value = value;
		value /= base;
		*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
	} while (value);

	// Apply negative sign
	if (tmp_value < 0) *ptr++ = '-';
	*ptr-- = '\0';
	while (ptr1 < ptr) {
		tmp_char = *ptr;
		*ptr-- = *ptr1;
		*ptr1++ = tmp_char;
	}
	return result;
}

SODIUM_SHARED_API char* mkStrdup(HANDLE pHeapHandle, const char *sourceStr, const char *sourceFile, int sourceLine) {

	if (sourceStr == NULL) {
		return NULL;
	}
	size_t  len = strlen(sourceStr);

	char *target = (char *) mkMalloc(pHeapHandle, len + 1, sourceFile, sourceLine);

	strncpy_s(target, len + 1, sourceStr, len);
	target[len] = '\0';
	return target;
}

SODIUM_SHARED_API wchar_t* mkStrdupW(HANDLE pHeapHandle, const wchar_t *sourceStr, const char *sourceFile, int sourceLine) {

	if (sourceStr == NULL) {
		return NULL;
	}
	size_t  len = wcslen(sourceStr);

	wchar_t *target = (wchar_t*)mkMalloc(pHeapHandle, (size_t) ((len + 1) * sizeof(wchar_t)), sourceFile, sourceLine);

	wcsncpy_s(target, len+1, sourceStr, len+1);

	return target;
}

SODIUM_SHARED_API char* mkStrdupN(HANDLE pHeapHandle, const char *sourceStr, int len, const char *sourceFile, int sourceLine) {
	if (sourceStr == NULL) {
		return NULL;
	}
	char *target = (char *)mkMalloc(pHeapHandle, len + 1, sourceFile, sourceLine);
	strncpy_s(target, len + 1, sourceStr, len);
	target[len] = '\0';
	return target;
}


SODIUM_SHARED_API 
char *
mkStrcat(
	HANDLE pHeapHandle, 
	const char *sourceFile, 
	int sourceLine, 
	const char *first, ...
)
{
	size_t memsize = 0;
	char *tagSemanticValue = NULL;
	const char *str = first;
	va_list vl;

	//  szTypes is the last argument specified; you must access   
	//  all others using the variable-argument macros.  
	va_start(vl, first);
	str = first;
	while (str != NULL) {
		if (memsize == 0) {
			if (str) {
				if (strlen(str) > 0) {
					memsize = strlen(str) + 1;
					tagSemanticValue = (char *)mkMalloc(pHeapHandle, memsize, sourceFile, sourceLine);
					strcpy_s(tagSemanticValue, memsize, str);
				}
				else {
					// we got "" string. that is, it is not NULL but an empty string
					memsize = 2;
					tagSemanticValue = (char *)mkMalloc(pHeapHandle, memsize, sourceFile, sourceLine);
					strcpy_s(tagSemanticValue, memsize, "");
				}
			}
		}
		else {
			memsize += strlen(str) + 1;
			tagSemanticValue = (char *)mkReAlloc(pHeapHandle, tagSemanticValue, memsize);
			strcat_s(tagSemanticValue, memsize, str);
		}
		str = va_arg(vl, char*);
	};
	va_end(vl);

	return tagSemanticValue;
}

SODIUM_SHARED_API 
wchar_t *
mkStrcatW(
	HANDLE pHeapHandle, 
	const char *sourceFile, 
	int sourceLine, 
	const wchar_t *first, ...
)
{
	size_t memsize = 0;
	wchar_t * tagSemanticValue = NULL;
	const wchar_t * str = first;
	va_list vl;

	//  szTypes is the last argument specified; you must access   
	//  all others using the variable-argument macros.  
	va_start(vl, first);
	str = first;
	while (str != NULL) {
		if (memsize == 0) {
			if (str) {
				size_t strSize = wcslen(str);
				if (strSize > 0) {
					memsize = (strSize * sizeof(wchar_t)) + sizeof(wchar_t);
					tagSemanticValue = (wchar_t *)mkMalloc(pHeapHandle, memsize, sourceFile, sourceLine);
					//strcpy_s(tagSemanticValue, memsize, str);
					wcsncpy(tagSemanticValue, str, strSize);
				}
				else {
					// we got "" string. that is, it is not NULL but an empty string
					memsize = sizeof(wchar_t);
					tagSemanticValue = (wchar_t *)mkMalloc(pHeapHandle, memsize, sourceFile, sourceLine);
					//strcpy_s(tagSemanticValue, memsize, "");
					wcsncpy(tagSemanticValue, L"", sizeof(wchar_t));
				}
			}
		}
		else {
			size_t strSize = wcslen(str);
			memsize += (strSize * sizeof(wchar_t)) + sizeof(wchar_t);
			tagSemanticValue = (wchar_t *)mkReAlloc(pHeapHandle, tagSemanticValue, memsize);
			//strcat_s(tagSemanticValue, memsize, str);
			wcsncat(tagSemanticValue, str, strSize);
		}
		str = va_arg(vl, wchar_t *);
	};
	va_end(vl);

	return tagSemanticValue;
}


SODIUM_SHARED_API void *mkMalloc(HANDLE pHeapHandle, size_t memsize, const char *sourceFile, int sourceLine) {
	void *retVal = HeapAlloc(pHeapHandle, HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, memsize); //HEAP_GENERATE_EXCEPTIONS|
#ifdef HTSQL_MEMORY_LEAK_DEBUG
	htsqlDebug_AddMallocEntry(pHeapHandle, retVal, memsize, sourceFile, sourceLine);
#endif // HTSQL_MEMORY_LEAK_DEBUG
	return retVal;
}


SODIUM_SHARED_API void mkFree(HANDLE pHeapHandle, void *ptr) {
#ifdef HTSQL_MEMORY_LEAK_DEBUG
	htsqlDebug_DeleteMallocEntry(pHeapHandle, ptr);
#endif // HTSQL_MEMORY_LEAK_DEBUG

	HeapFree(pHeapHandle, HEAP_ZERO_MEMORY, ptr); //HEAP_GENERATE_EXCEPTIONS
}

SODIUM_SHARED_API void mkFreeAdv(HANDLE pHeapHandle, void **ptr) {
	if (*ptr) {
		DWORD ret = HeapFree(pHeapHandle, HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, *ptr); //HEAP_GENERATE_EXCEPTIONS
		if (ret == 0) {
			//__sendErrorResponse(currentMKSession, NULL, "hata", "");
		}
#ifdef HTSQL_MEMORY_LEAK_DEBUG
		htsqlDebug_DeleteMallocEntry(pHeapHandle, *ptr);
#endif // HTSQL_MEMORY_LEAK_DEBUG
		*ptr = NULL;
	}
	else {
		//__sendErrorResponse(pHeapHandle, NULL, "NULL value passed to the MkFreeAd", "");
	}
}


SODIUM_SHARED_API void *mkReAlloc(HANDLE pHeapHandle, void *ptr, size_t newmemsize) {
	void *retVal = HeapReAlloc(pHeapHandle, HEAP_ZERO_MEMORY | HEAP_GENERATE_EXCEPTIONS, ptr, newmemsize); //HEAP_GENERATE_EXCEPTIONS|
#ifdef HTSQL_MEMORY_LEAK_DEBUG
	htsqlDebug_UpdateMallocEntry(pHeapHandle, ptr, retVal, newmemsize);
#endif // HTSQL_MEMORY_LEAK_DEBUG
	return retVal;
}
