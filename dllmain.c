/**
 * This file is part of Sodium Language project
 *
 * Copyright � 2020 Murad Karaka� <muradkarakas@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License v3.0
 * as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 *	https://choosealicense.com/licenses/gpl-3.0/
 */
#include "pch.h"

#include "dllmain.h"

#ifndef  _SH_DENYWR
#define _SH_DENYWR      0x20    // deny write mode
#endif // ! _SH_DENYWR

#ifndef  _SH_DENYNO
#define _SH_DENYNO      0x40    // deny none mode
#endif





SODIUM_SHARED_API BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {

	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: {
#ifdef HTSQL_DEBUG

#endif
			break;
		}
		case DLL_THREAD_ATTACH: {
			break;
		}
		case DLL_THREAD_DETACH: {
			break;
		}
		case DLL_PROCESS_DETACH: {
#ifdef HTSQL_DEBUG

#endif
			break;
		}
	}
	return TRUE;
}

