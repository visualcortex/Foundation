/******************************************************************************
 * @file
 * @author Ivan Makarov <im.visualcortex@gmail.com>
 * 
 * @section LICENSE
 *
 * Copyright (C) 2012, Ivan Makarov
 * Licensed under the MIT license.
 *
 *****************************************************************************/

#include "../Precompiled.hpp"

#include "Platform.hpp"

#define SOURCE_CLASS "Dream.Foundation.IO.Platform"

namespace Dream
{
	namespace IO
	{
		namespace
		{
			BOOL (WINAPI *g_Wow64DisableWow64FsRedirection)(PVOID*) = nullptr;
			BOOL (WINAPI *g_Wow64RevertWow64FsRedirection)(PVOID) = nullptr;

			bool InitializePlatform() throw();
			bool g_WasPlatformInitialized = InitializePlatform();

			bool InitializePlatform() throw()
			{
				HMODULE hlibKernel32 = LoadLibraryA("kernel32.dll");
				if (hlibKernel32 != nullptr)
				{
					FARPROC address = 
						GetProcAddress(hlibKernel32, "Wow64DisableWow64FsRedirection");
					if (address != nullptr)
						*(FARPROC*)&g_Wow64DisableWow64FsRedirection = address;

					address = 
						GetProcAddress(hlibKernel32, "Wow64RevertWow64FsRedirection");
					if (address != nullptr)
						*(FARPROC*)&g_Wow64RevertWow64FsRedirection = address;
				
					FreeLibrary(hlibKernel32);
				}

				return true;
			}
		}

		BOOL WINAPI Platform::Wow64DisableWow64FsRedirection(PVOID* OldValue)
		{
			return g_Wow64DisableWow64FsRedirection != nullptr ? 
				g_Wow64DisableWow64FsRedirection(OldValue) : TRUE;
		}

		BOOL WINAPI Platform::Wow64RevertWow64FsRedirection(PVOID OldValue)
		{
			return g_Wow64RevertWow64FsRedirection != nullptr ? 
				g_Wow64RevertWow64FsRedirection(OldValue) : TRUE;
		}
	}
}
