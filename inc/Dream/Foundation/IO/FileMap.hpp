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

#include <Dream/Foundation/IO/FileStream.hpp>
#include <Dream/Foundation/IO/FileMapAccessRights.hpp>

namespace Dream
{
	namespace IO 
	{
		class FileMap : Noncopyable
		{
			public:
				FileMap() throw();
				FileMap(
					 __in FileStream *stream,
					 __in const string &name,
					 __in uint64 maxsize,
					 __in FileMapAccessRights accessRights);

				~FileMap() throw();

			public:
				/// Indicates if the map is still good.
				operator void* () const throw();

			public:
				/** Opens the map
				 *	\param stream The stream from which to create map
				 *	\param accessRights The access rights to the map
				 *	\param maxsize The maximum size of the map
				 *	\param name The name of the map
				 *	\note Provide value "0" for maxsize to map the whole stream
				 */
				void open
					(__in FileStream *stream,
					 __in const string &name,
					 __in uint64 maxsize,
					 __in FileMapAccessRights accessRights);

				void close() throw();

			public:
				/// Gets the name of the map
				const string& getName() const throw();
				/// Gets the max size of the map
				uint64 getMaxSize() const throw();
				/// Gets the access rights to the map
				FileMapAccessRights getAccesRights() const throw();

			private:
				void *m_handle;
				FileStream *m_stream;
				string m_name;
				uint64 m_maxsize;
				FileMapAccessRights m_accessRights;
		};
	}
}
