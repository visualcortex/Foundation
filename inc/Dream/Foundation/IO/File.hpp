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

#include <Dream/Foundation/IO/FileFeatures.hpp>

namespace Dream
{
	namespace IO 
	{
		class File
		{
			public:
				/** Determines whether the specified file exists
				 */
				static bool Exists
					(__in const string &pathFileToCheck);

			public:
				/** Gets the attributes of the file
				 */
				static FileFeatures GetFeatures
					(__in const string &path);

			public:
				/** Copies an existing file to a new file
				 */
				static void Copy
					(__in const string &pathSrcFile, 
					 __in const string &pathDstFile,
					 __in bool shouldOverrideIfExists = false);

				/** Moves an existing file
				 */
				static void Move
					(__in const string &pathSrcFile, 
					 __in const string &pathDstFile);

				/** Removes an existing file
				 */
				static void Remove
					(__in const string &pathFileToRemove);

				/** Reads the contents of the file into a byte array
				 */
				static ByteArray ReadAllBytes
					(__in const string &pathFileToRead);
		};
	}
}
