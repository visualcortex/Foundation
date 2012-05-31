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

#include <Dream/Foundation/IO/FileStream.hpp>
#include <Dream/Foundation/IO/Exception.hpp>

#include "Platform.hpp"

#define SOURCE_CLASS "Dream.Foundation.IO.FileStream"

namespace Dream 
{
	namespace IO
	{
		namespace
		{
			const FileOpenMode DEFAULT_OPEN_MODE = FileOpenMode::OpenExisting;
			const FileAccessRights DEFAULT_ACCESS_RIGHTS = FileAccessRights::Read;
			const FileShareMode DEFAULT_SHARE_MODE = FileShareMode::Read;
		}

		FileStream::FileStream() throw()
			: m_handle(INVALID_HANDLE_VALUE),
			  m_openMode(DEFAULT_OPEN_MODE),
			  m_accessRights(DEFAULT_ACCESS_RIGHTS),
			  m_shareMode(DEFAULT_SHARE_MODE)
		{}

		FileStream::FileStream
			(__in const string &pathFile,
			 __in FileOpenMode openMode,
			 __in FileAccessRights accessRights,
			 __in FileShareMode shareMode)
			: m_handle(INVALID_HANDLE_VALUE),
			  m_openMode(DEFAULT_OPEN_MODE),
			  m_accessRights(DEFAULT_ACCESS_RIGHTS),
			  m_shareMode(DEFAULT_SHARE_MODE)
		{
			open(pathFile, openMode, accessRights, shareMode);
		}

		FileStream::~FileStream() throw()
		{
			close();
		}

		FileStream::operator void*() const throw()
		{
			return m_handle;
		}

		void FileStream::open
			(__in const string &pathFile, 
			 __in FileOpenMode openMode, 
			 __in FileAccessRights accessRights, 
			 __in FileShareMode shareMode)
		{
			void *handle = ::CreateFileA(pathFile.c_str(), 
					Platform::FromFileAccessRights(accessRights),
					Platform::FromFileShareMode(shareMode),
					NULL,
					Platform::FromFileOpenMode(openMode),
					FILE_ATTRIBUTE_NORMAL,
					NULL);
			if (handle != INVALID_HANDLE_VALUE)
			{
				if (openMode != FileOpenMode::Append 
					|| ::SetFilePointer(handle, 0, 0, FILE_END) != INVALID_SET_FILE_POINTER)
				{
					m_handle = handle;
		 			m_pathFile = pathFile;
					m_openMode = openMode;
					m_accessRights = accessRights;
					m_shareMode = shareMode;

					return;
				}
			}

			result_t result = System::Environment::GetLastError();
			if (handle != INVALID_HANDLE_VALUE)
				::CloseHandle(handle);

			throw Exception(SOURCE_CLASS, result);
		}

		void FileStream::close() throw()
		{
			if (m_handle != INVALID_HANDLE_VALUE)
			{
				::CloseHandle(m_handle);

				m_handle = INVALID_HANDLE_VALUE;
				m_pathFile = "";
		  		m_openMode = DEFAULT_OPEN_MODE;
				m_accessRights = DEFAULT_ACCESS_RIGHTS;
				m_shareMode = DEFAULT_SHARE_MODE;			
			}
		}

		const string& FileStream::getFilePath() const throw()
		{
			return m_pathFile;
		}
	
		FileOpenMode FileStream::getOpenMode() const throw()
		{
			return m_openMode;
		}
	
		FileAccessRights FileStream::getAccessRights() const throw()
		{
			return m_accessRights;
		}
	
		FileShareMode FileStream::getShareMode() const throw()
		{
			return m_shareMode;
		}

		uint64 FileStream::getSize() const
		{
			DWORD sizeStreamHigh = 0;
			DWORD sizeStreamLow = ::GetFileSize(m_handle, &sizeStreamHigh);

			if (sizeStreamLow != INVALID_FILE_SIZE)
				return Convert::ToUInt64(sizeStreamLow, sizeStreamHigh);

			throw Exception(SOURCE_CLASS,
				System::Environment::GetLastError());
		}
	
		void FileStream::setSize(__in uint64 sizeStreamNew)
		{
			uint32 sizeStreamLow = 0;
			uint32 sizeStreamHigh = 0;

			Convert::ToUInt32(sizeStreamNew, &sizeStreamLow, &sizeStreamHigh);

			LONG distanceToMoveLow = sizeStreamLow;
			LONG distanceToMoveHigh = sizeStreamHigh;

			if (::SetFilePointer(m_handle, distanceToMoveLow, &distanceToMoveHigh, FILE_BEGIN) 
					!= INVALID_SET_FILE_POINTER && ::SetEndOfFile(m_handle) != 0)
			{
				return;
			}

			throw Exception(SOURCE_CLASS, 
				System::Environment::GetLastError());
		}

		size_t FileStream::read(__out byte *buffer, __in size_t numBytesToRead)
		{
			DWORD numBytesRead = 0;
			if (::ReadFile(m_handle, buffer, 
						numBytesToRead, &numBytesRead, NULL) != 0)
				return numBytesRead;

			throw Exception(SOURCE_CLASS, 
				System::Environment::GetLastError());
		}

		void FileStream::write(__in const byte *buffer, __in size_t numBytesToWrite)
		{
			DWORD numBytesWritten = 0;
			if (::WriteFile(m_handle, buffer, numBytesToWrite, &numBytesWritten, NULL) != 0)
			{
				if (numBytesWritten == numBytesToWrite)
					return;

				throw Exception(SOURCE_CLASS, 
					DREAM_E_WRITTEN_LESS_THAN_SPECIFIED);
			}

			throw Exception(SOURCE_CLASS, 
				System::Environment::GetLastError());
		}
	}
}
