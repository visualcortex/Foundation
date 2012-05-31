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
#include <Dream/Foundation/IO/FileOpenMode.hpp>
#include <Dream/Foundation/IO/FileShareMode.hpp>

namespace Dream
{
	namespace IO
	{
		class FileStream : Noncopyable
		{
			public:
				FileStream() throw();
				FileStream
					(__in const string &pathFile,
					 __in FileOpenMode openMode,
					 __in FileAccessRights accessRights,
					 __in FileShareMode shareMode);

				~FileStream() throw();

			public:
				/// Indicates if the stream is still good.
				operator void*() const throw();

			public:
				/** Opens the stream
				 *	\param pathFile The path of the file to be created or opened
				 *	\param openMode The open mode of the file
				 *	\param accessRights The desired access to the file
				 *	\param shareMode The sharing mode of the file
				 */
				void open
					(__in const string &pathFile,
					 __in FileOpenMode openMode,
					 __in FileAccessRights accessRights,
					 __in FileShareMode shareMode);

				/// Closes the stream
				void close() throw();

			public:
				/// Gets file path
				const string& getFilePath() const throw();
				/// Gets open mode
				FileOpenMode getOpenMode() const throw();
				/// Gets access rights
				FileAccessRights getAccessRights() const throw();
				/// Gets share mode
				FileShareMode getShareMode() const throw();

			public:
				/// Gets the length in bytes of the stream
				uint64 getSize() const;
				/// Sets the length of this stream to the given value
				void setSize(__in uint64 sizeStreamNew);

			public:
				/** Reads a block of bytes from stream
				 *	\param buffer A pointer to the buffer, used to store data
				 *	\param numBytesToRead The number of bytes to be read
				 *	\return Number of bytes read
				 */
				size_t read(__out byte *buffer, __in size_t numBytesToRead);

				/** Writes a block of bytes to stream
				 *	\param buffer A pointer to the buffer, containing data to be written
				 *	\param numBytesToWriter The number of bytes to be written
				 */
				void write(__in const byte *buffer, __in size_t numBytesToWrite);

			private:
				void *m_handle;
				string m_pathFile;
				FileOpenMode m_openMode;
				FileAccessRights m_accessRights;
				FileShareMode m_shareMode;
		};
	}
}
