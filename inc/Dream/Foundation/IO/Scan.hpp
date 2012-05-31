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

#include <Dream/Foundation/IO/ScanListener.hpp>

namespace Dream
{
	namespace IO
	{
		/** Filesystem Scan
		 */
		class Scan
		{
			public:
				Scan();

			public:
				/** Path of file, directory or drive to scan for
	             *  \note Set this field to "${SYSTEM}" in order to scan all logical drives
				 */
	            string path;

	            /// File filter (PERL Regular Expessions)
	            string filter;

				/// Recursive directory scan
	            bool isRecursive;

				/// Scan listener
	            std::shared_ptr<IScanListener> listener;

			public:
				/// Start scan
				void run();
		};
	}
}
