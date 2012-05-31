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

#include <Dream/Foundation/Essential.hpp>

namespace Dream
{
	namespace IO
	{
		class Directory
		{
			public:
				/** Determines whether the specified directory exists
				 */
				static bool Exists
					(__in const string &pathDirToCheck);

	        public:
	            /** Returns the number of files in a specified directory
	             */
	            static size_t GetNumFiles
	                (__in const string &pathDir,
	                 __in bool isRecursive);

			public:
				/** Creates all directories and subdirectories in the specified path
				 */
				static void Create
					(__in const string &pathDirToCreate);

			public:
				/** Copies an existing directory, including sub-directories and files
				 */
				static void Copy
					(__in const string &pathSrcDir, 
					 __in const string &pathDstDir);

				/** Moves an existing directory, including sub-directories and files
				 */
				static void Move
					(__in const string &pathSrcDir, 
					 __in const string &pathDstDir);

				/** Removes an existing directory, including sub-directories and files
				 */
				static void Remove
					(__in const string &pathDirToRemove);
		};
	}
}
