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

#include <Dream/Foundation/System/Environment.hpp>
#include <Dream/Foundation/System/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.System.Environment"

namespace Dream
{
	namespace System
	{
		string Environment::GetMachineName()
		{
			CHAR name[MAX_COMPUTERNAME_LENGTH + 1];
			DWORD bufsize = MAX_COMPUTERNAME_LENGTH + 1;

			if (::GetComputerNameA(name, &bufsize) != 0)
				return string(name);

			throw Exception(SOURCE_CLASS);
		}

		result_t Environment::GetLastError() throw()
		{
			DWORD value = ::GetLastError();
			return HRESULT_FROM_WIN32(value);
		}

		StringArray Environment::GetLogicalDrives()
		{
			static const char *DRIVES[] = 
			{
				"A:\\", "B:\\", "C:\\", "D:\\", "E:\\", "F:\\", "G:\\",
				"H:\\", "I:\\", "J:\\", "K:\\", "L:\\", "M:\\", "N:\\",
				"O:\\", "P:\\", "Q:\\", "R:\\", "S:\\", "T:\\", "U:\\",
				"V:\\", "W:\\", "X:\\", "Y:\\", "Z:\\"
			};

			DWORD drives = ::GetLogicalDrives();
			if (drives != 0)
			{
				StringArray result;
				for (DWORD i = 2; i < 26; i++)
				{
					if ((drives >> i) & 1)
					{
						const char *drive = DRIVES[i];
						DWORD typeDrive = ::GetDriveTypeA(drive);
						if (typeDrive == DRIVE_REMOVABLE
							|| typeDrive == DRIVE_FIXED)
						{
							result.push_back(drive);
						}
					}
				}

				return result;
			}

			throw Exception(SOURCE_CLASS);
		}

		string Environment::GetOSVersion()
		{
			OSVERSIONINFO version;
			version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

			if (::GetVersionEx(&version) != 0)
			{
				std::ostringstream stream;
				stream << version.dwMajorVersion << '.' << 
					version.dwMinorVersion << '.' << version.dwBuildNumber;

				return stream.str();
			}

			throw Exception(SOURCE_CLASS);
		}
	}
}
