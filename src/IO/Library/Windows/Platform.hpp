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

#pragma once

#include <Dream/Foundation/IO/FileAccessRights.hpp>
#include <Dream/Foundation/IO/FileFeatures.hpp>
#include <Dream/Foundation/IO/FileMapAccessRights.hpp>
#include <Dream/Foundation/IO/FileOpenMode.hpp>
#include <Dream/Foundation/IO/FileSeekMode.hpp>
#include <Dream/Foundation/IO/FileShareMode.hpp>
#include <Dream/Foundation/IO/FileViewAccessRights.hpp>

namespace Dream
{
	namespace IO
	{
		class Platform
		{
			public:
				static BOOL WINAPI Wow64DisableWow64FsRedirection(PVOID* OldValue);
				static BOOL WINAPI Wow64RevertWow64FsRedirection(PVOID OldValue);

			public:
				static DWORD FromFileAccessRights(__in FileAccessRights value) throw()
				{
					DWORD result = 0;
					switch (value)
					{
						case FileAccessRights::Read: result = GENERIC_READ; break;
						case FileAccessRights::Write: result = GENERIC_WRITE; break;
						case FileAccessRights::ReadWrite: result = GENERIC_READ|GENERIC_WRITE;break;
						default:
							DREAM_NODEFAULT;
					}

					return result;
				}

				static DWORD FromFileOpenMode(__in FileOpenMode value) throw()
				{
					DWORD result = 0;
					switch (value)
					{
						case FileOpenMode::Create: result = CREATE_ALWAYS; break;
						case FileOpenMode::CreateNew: result = CREATE_NEW; break;
						case FileOpenMode::Open: result = OPEN_ALWAYS; break;
						case FileOpenMode::OpenExisting: result = OPEN_EXISTING; break;
						case FileOpenMode::Append: result = OPEN_EXISTING; break;
						case FileOpenMode::Truncate: result = TRUNCATE_EXISTING; break;
						default:
							DREAM_NODEFAULT;
					}

					return result;
				}

				static DWORD FromFileShareMode(__in FileShareMode value) throw()
				{
					DWORD result = 0;
					switch (value)
					{
						case FileShareMode::None: result = 0; break;
						case FileShareMode::Read: result = FILE_SHARE_READ; break;
						case FileShareMode::Write: result = FILE_SHARE_WRITE; break;
						case FileShareMode::ReadWrite: result = FILE_SHARE_READ|FILE_SHARE_WRITE; break;
						case FileShareMode::Delete: result = FILE_SHARE_DELETE; break;
						default:
							DREAM_NODEFAULT;
					}

					return result;
				}

				static DWORD FromFileSeekMode(__in FileSeekMode value) throw()
				{
					DWORD result = 0;
					switch (value)
					{
						case FileSeekMode::Begin: result = FILE_BEGIN; break;
						case FileSeekMode::Current: result = FILE_CURRENT; break;
						case FileSeekMode::End: result = FILE_END; break;
						default:
							DREAM_NODEFAULT;
					}

					return result;
				}

				static FileFeatures ToFileFeatures(__in DWORD value)
				{
					FileFeatures result;

					if (value & FILE_ATTRIBUTE_ARCHIVE)       result |= FileFeature::Archive;
					if (value & FILE_ATTRIBUTE_COMPRESSED)    result |= FileFeature::Compressed;
					if (value & FILE_ATTRIBUTE_DIRECTORY)     result |= FileFeature::Directory;
					if (value & FILE_ATTRIBUTE_ENCRYPTED)     result |= FileFeature::Encrypted;
					if (value & FILE_ATTRIBUTE_HIDDEN)        result |= FileFeature::Hidden;
					if (value & FILE_ATTRIBUTE_NORMAL)        result |= FileFeature::Normal;
					if (value & FILE_ATTRIBUTE_OFFLINE)       result |= FileFeature::Offline;
					if (value & FILE_ATTRIBUTE_READONLY)      result |= FileFeature::Readonly;
					if (value & FILE_ATTRIBUTE_REPARSE_POINT) result |= FileFeature::ReparsePoint;
					if (value & FILE_ATTRIBUTE_SPARSE_FILE)   result |= FileFeature::SparseFile;
					if (value & FILE_ATTRIBUTE_SYSTEM)        result |= FileFeature::System;
					if (value & FILE_ATTRIBUTE_TEMPORARY)     result |= FileFeature::Temporary;
					if (value & FILE_ATTRIBUTE_VIRTUAL)       result |= FileFeature::Virtual;

					return result;
				}

				static DWORD FromFileMapAccessRights(__in FileMapAccessRights value)
				{
					DWORD result = 0;
					switch (value)
					{
						case FileMapAccessRights::Read: result = PAGE_READONLY; break;
						case FileMapAccessRights::ReadWrite: result = PAGE_READWRITE; break;
						case FileMapAccessRights::ExecuteRead: result = PAGE_EXECUTE_READ; break;
						case FileMapAccessRights::ExecuteReadWrite: result = PAGE_EXECUTE_READWRITE; break;
						default:
							DREAM_NODEFAULT;
					}

					return result;
				}

				static DWORD FromFileViewAccessRights(__in FileViewAccessRights value)
				{
					DWORD result = 0;
					switch (value)
					{
						case FileViewAccessRights::Read: result = FILE_MAP_READ; break;
						case FileViewAccessRights::Write: result = FILE_MAP_WRITE; break;
						case FileViewAccessRights::ReadWrite: result = FILE_MAP_ALL_ACCESS; break;
						default:
							DREAM_NODEFAULT;
					}

					return result;
				}
		};
	}
}
