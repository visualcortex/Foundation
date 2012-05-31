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

#include <Dream/Foundation/IO/File.hpp>
#include <Dream/Foundation/IO/Exception.hpp>
#include <Dream/Foundation/IO/FileStream.hpp>

#include "Platform.hpp"

#define SOURCE_CLASS "Dream.Foundation.IO.File"

namespace Dream
{
	namespace IO
	{
		bool File::Exists(__in const string &pathFileToCheck)
		{
			DWORD attrs = ::GetFileAttributesA(pathFileToCheck.c_str());
			return attrs != INVALID_FILE_ATTRIBUTES && 
					(attrs & FILE_ATTRIBUTE_DIRECTORY) == 0;
		}

		FileFeatures File::GetFeatures(__in const string &pathFile)
		{
			DWORD attrs = ::GetFileAttributesA(pathFile.c_str());
			if (attrs != INVALID_FILE_ATTRIBUTES)
				return Platform::ToFileFeatures(attrs);

			throw Exception(SOURCE_CLASS,
					System::Environment::GetLastError());
		}

		void File::Copy
			(__in const string &pathSrcFile,
			 __in const string &pathDstFile,
			 __in bool shouldOverrideIfExists)
		{
			if (::CopyFileA(pathSrcFile.c_str(), pathDstFile.c_str(), 
							shouldOverrideIfExists ? FALSE : TRUE) == 0)
				throw Exception(SOURCE_CLASS, System::Environment::GetLastError());
		}

		void File::Move
			(__in const string &pathSrcFile, 
			 __in const string &pathDstFile)
		{
			if (::MoveFileA(pathSrcFile.c_str(), pathDstFile.c_str()) == 0)
				throw Exception(SOURCE_CLASS, System::Environment::GetLastError());
		}

		void File::Remove(__in const string &pathFileToRemove)
		{
			if (::DeleteFileA(pathFileToRemove.c_str()) == 0)
				throw Exception(SOURCE_CLASS, System::Environment::GetLastError());
		}

		ByteArray File::ReadAllBytes(__in const string &pathFile)
		{
			ByteArray retval;

			FileStream stream(pathFile,
				FileOpenMode::OpenExisting,
				FileAccessRights::Read,
				FileShareMode::Read);

			/// @todo FIX THIS STUPID WORKAROUND!!!
			uint64 sizeStream64 = stream.getSize();
			if (sizeStream64 > MAX_REASONABLE_SIZE)
				throw Exception(SOURCE_CLASS, DREAM_E_FILE_IS_TOO_LARGE);

			size_t sizeStream = static_cast<size_t>(sizeStream64);
			retval.resize(sizeStream);

			size_t numBytesRead = stream.read(&retval[0], sizeStream);
			if (numBytesRead != sizeStream)
				throw Exception(SOURCE_CLASS, DREAM_E_READ_LESS_THAN_SPECIFIED);

			return retval;
		}
	}
}
