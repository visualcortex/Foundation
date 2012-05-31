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

#include <Dream/Foundation/IO/Directory.hpp>
#include <Dream/Foundation/IO/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.IO.Directory"

namespace Dream 
{
	namespace IO 
	{
		namespace
		{
			size_t ScanDirectory
				( __in const string &pathParentDir,
				  __in bool isRecursive)
			{
				string pattern = pathParentDir + "\\*.*";

				size_t numFiles = 0;

				struct _finddata_t file;
				intptr_t hFile = _findfirst(pattern.c_str(), &file);
				if (hFile != -1L )
				{
					do
					{
						if (_stricmp(file.name, ".") == 0 || _stricmp(file.name, "..") == 0)
							continue;
					
						if ((file.attrib & _A_SUBDIR) == 0)
						{
							numFiles++;
						}
						else if (isRecursive)
						{
							numFiles += ScanDirectory
								((pathParentDir + "\\") + file.name, isRecursive);
						}
					}
					while (_findnext(hFile, &file) == 0);
			
					_findclose(hFile);
				}

				return numFiles;
			}
		}

		void Directory::Create(__in const string &pathDirToCreate)
		{
			if (CreateDirectoryA(pathDirToCreate.c_str(), NULL) != 0)
				return;

			throw Exception(SOURCE_CLASS,
					System::Environment::GetLastError());
		}

		bool Directory::Exists(__in const string &pathDirToCheck)
		{
			DWORD attrs = ::GetFileAttributesA(pathDirToCheck.c_str());
			return attrs != INVALID_FILE_ATTRIBUTES && 
					(attrs & FILE_ATTRIBUTE_DIRECTORY) != 0;
		}

		size_t Directory::GetNumFiles
			(__in const string &pathDir,
			 __in bool isRecursive)
		{
			return ScanDirectory(pathDir, isRecursive);

		}

		/// @todo IMPLEMENT ME!!!
		void Directory::Copy
			(__in const string &pathSrcDir,
			 __in const string &pathDstDir)
		{
			DREAM_UNREFERENCED_PARAMETER(pathSrcDir);
			DREAM_UNREFERENCED_PARAMETER(pathDstDir);
		}

		void Directory::Move
			(__in const string &pathSrcDir, 
			 __in const string &pathDstDir)
		{
			if (::MoveFileA(pathSrcDir.c_str(), pathDstDir.c_str()) != 0)
				return;

			throw Exception(SOURCE_CLASS, 
					System::Environment::GetLastError());
		}

		/// @todo IMPLEMENT ME!!!
		void Directory::Remove(__in const string &pathDirToRemove)
		{
			DREAM_UNREFERENCED_PARAMETER(pathDirToRemove);
		}
	}
 }
