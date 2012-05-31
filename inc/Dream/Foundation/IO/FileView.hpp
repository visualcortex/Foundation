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

#include <Dream/Foundation/IO/FileMap.hpp>
#include <Dream/Foundation/IO/FileViewAccessRights.hpp>

namespace Dream
{
	namespace IO
	{
		class FileView : Noncopyable
		{
			public:
				FileView() throw();
				FileView
					(__in FileMap *mapFile,
					 __in uint64 offset,
					 __in size_t size,
					 __in FileViewAccessRights accessRights);

				~FileView() throw();

			public:
				/// Indicates if the view is still good.
				operator void* () const throw();

			public:
				byte operator[] (__in size_t i) const;

			public:
				/** Opens the view
				 *	\param mapFile The file map from which to create the view
				 *	\param accessRights The access rights to the view
				 *	\param offset The view offset in the map
				 *	\param size The view size
				 *	\note Provide value "0" for size to extend view on the whole map
				 */
				void open
					(__in FileMap *mapFile,
					 __in uint64 offset,
					 __in size_t size,
					 __in FileViewAccessRights accessRights);

				/// Closes the view
				void close() throw();

			public:
				/// Gets offset of the view
				uint64 getOffset() const throw();
				/// Gets size of the view
				size_t getSize() const throw();
				/// Gets access rights to the view
				FileViewAccessRights getAccessRights() const throw();

			public:
				/** Seeks in the view
				 *	\param offset The offset of data
				 *	\param size The size of data
	             *  \return The pointer to data specified by offset
				 */
				byte* seek(__in size_t offset, __in size_t size);

	            /** Seeks in the view
				 *	\param offset The offset of data
				 *	\param size The size of data
	             *  \return The pointer to data specified by offset
				 */
	            const byte* seek(__in size_t offset, __in size_t size) const;

	            /** Seeks in the view
				 *	\param offset The offset of data
	             *  \param count The number of elements of type T
	             *  \return The pointer to data specified by offset
				 */
				template<class T>
					T* seek(__in size_t offset, __in size_t count = 1) {
						return reinterpret_cast<T*>(seek(offset, sizeof(T)*count));
					}

				/** Seeks in the view
				 *	\param offset The offset of data
	             *  \param count The number of elements of type T
	             *  \return The pointer to data specified by offset
				 */
				template<class T>
					const T* seek(__in size_t offset, __in size_t count = 1) const {
						return reinterpret_cast<T*>(seek(offset, sizeof(T)*count));
					}
				
			private:
				void *m_handle;
				FileMap *m_mapFile;
				uint64 m_offset;
				size_t m_size;
				FileViewAccessRights m_accessRights;
		};
	}
}
