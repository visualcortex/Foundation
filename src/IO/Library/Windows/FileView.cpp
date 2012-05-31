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

#include <Dream/Foundation/IO/FileView.hpp>
#include <Dream/Foundation/IO/Exception.hpp>

#include "Platform.hpp"

#define SOURCE_CLASS "Dream.Foundation.IO.FileView"

namespace Dream
{
	namespace IO
	{
		namespace 
		{
			const FileViewAccessRights DEFAULT_ACCESS_RIGHTS = FileViewAccessRights::Read;
		}

		FileView::FileView() throw()
			: m_handle			(nullptr)
			, m_mapFile			(nullptr)
			, m_offset			(0)
			, m_size			(0)
			, m_accessRights	(DEFAULT_ACCESS_RIGHTS)
		{}

		FileView::FileView
			(__in FileMap *mapFile,
			 __in uint64 offset,
			 __in size_t size,
			 __in FileViewAccessRights accessRights)
			: m_handle			(nullptr)
			, m_mapFile			(nullptr)
			, m_offset			(0)
			, m_size			(0)
			, m_accessRights	(DEFAULT_ACCESS_RIGHTS)
		{
			open(mapFile, offset, size, accessRights);
		}

		FileView::~FileView() throw()
		{
			close();
		}

		FileView::operator void* () const throw()
		{
			return m_handle;
		}

		byte FileView::operator[] (__in size_t i) const
		{
			if (i < m_size)
				return static_cast<byte*>(m_handle)[i];

			throw Exception(SOURCE_CLASS, DREAM_E_OUT_OF_RANGE);
		}

		/// @todo 64bit!!!
		void FileView::open
			(__in FileMap *mapFile,
			 __in uint64 offset,
			 __in size_t size,
			 __in FileViewAccessRights accessRights)
		{
			uint32 offsetLow = 0;
			uint32 offsetHigh = 0;

			Convert::ToUInt32(offset, &offsetLow, &offsetHigh);

			HANDLE handle = ::MapViewOfFile(mapFile->operator void*(), 
				Platform::FromFileViewAccessRights(accessRights), offsetHigh, offsetLow, size);
			if (handle == nullptr)
				throw Exception(SOURCE_CLASS, System::Environment::GetLastError());

			if (size == 0)
				size = mapFile->getMaxSize();

			m_handle = handle;
			m_mapFile = mapFile;
			m_offset = offset;
			m_size = size;
			m_accessRights = accessRights;
		}

		void FileView::close() throw()
		{
			if (m_handle != nullptr)
			{
				::UnmapViewOfFile(m_handle);

				m_handle = nullptr;
				m_mapFile = nullptr;
				m_offset = 0;
				m_size = 0;
				m_accessRights = DEFAULT_ACCESS_RIGHTS;
			}
		}

		uint64 FileView::getOffset() const throw()
		{
			return m_offset;
		}

		size_t FileView::getSize() const throw()
		{
			return m_size;
		}

		FileViewAccessRights FileView::getAccessRights() const throw()
		{
			return m_accessRights;
		}

		byte* FileView::seek(__in size_t offset, __in size_t size)
		{
			if (size == INVALID_SIZE)
				size = m_size;

			if (m_size < offset || m_size - offset < size)
				throw Exception(SOURCE_CLASS, DREAM_E_OUT_OF_RANGE);
			
			return static_cast<byte*>(m_handle) + offset;
		}

		const byte* FileView::seek(__in size_t offset, __in size_t size) const
		{
			if (size == INVALID_SIZE)
				size = m_size;

			if (m_size < offset || m_size - offset < size)
				throw Exception(SOURCE_CLASS, DREAM_E_OUT_OF_RANGE);
			
			return static_cast<const byte*>(m_handle) + offset;
		}
	}
}
