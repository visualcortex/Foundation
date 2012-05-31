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

#include <Dream/Foundation/IO/FileMap.hpp>
#include <Dream/Foundation/IO/Exception.hpp>

#include "Platform.hpp"

#define SOURCE_CLASS "Dream.Foundation.IO.FileMap"

namespace Dream
{
	namespace IO
	{
		namespace 
		{
			const FileMapAccessRights DEFAULT_ACCESS_RIGHTS = FileMapAccessRights::Read;
		}

		FileMap::FileMap() throw()
			: m_handle(NULL), m_stream(nullptr), 
				m_maxsize(0), m_accessRights(DEFAULT_ACCESS_RIGHTS)
		{}

		FileMap::FileMap
			(__in FileStream *stream,
			 __in const string &name,
			 __in uint64 maxsize,
			 __in FileMapAccessRights accessRights)
			: m_handle(nullptr), m_stream(nullptr), 
				m_maxsize(0), m_accessRights(DEFAULT_ACCESS_RIGHTS)
		{
			open(stream, name, maxsize, accessRights);
		}

		FileMap::~FileMap() throw()
		{
			close();
		}

		FileMap::operator void* () const throw()
		{
			return m_handle;
		}

		void FileMap::open
			(__in FileStream *stream,
			 __in const string &name,
			 __in uint64 maxsize,
			 __in FileMapAccessRights accessRights) 
		{
			uint32 maxSizeLow = 0;
			uint32 maxSizeHigh = 0;

			Convert::ToUInt32(maxsize, &maxSizeLow, &maxSizeHigh);		

			void *handle = ::CreateFileMappingA(stream->operator void*(), 
					nullptr, Platform::FromFileMapAccessRights(accessRights), 
					maxSizeHigh, maxSizeLow, name.empty() ? nullptr : name.c_str());
			if (handle == nullptr)
				throw Exception(SOURCE_CLASS, System::Environment::GetLastError());

			if (maxsize == 0)
				maxsize = stream->getSize();

			m_handle = handle;
			m_stream = stream;
			m_name = name;
			m_maxsize = maxsize;
			m_accessRights = accessRights;
		}

		void FileMap::close() throw()
		{
			if (m_handle != NULL)
			{
				::CloseHandle(m_handle);
			
				m_handle = NULL;
				m_stream = nullptr;
				m_name = "";
				m_maxsize = 0;
				m_accessRights = DEFAULT_ACCESS_RIGHTS;
			}
		}

		const string& FileMap::getName() const throw()
		{
			return m_name;
		}

		uint64 FileMap::getMaxSize() const throw()
		{
			return m_maxsize;
		}

		FileMapAccessRights FileMap::getAccesRights() const throw()
		{
			return m_accessRights;
		}
	}
}
