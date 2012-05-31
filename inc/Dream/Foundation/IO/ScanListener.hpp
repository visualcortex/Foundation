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
		/** Listener of the scanning process
		 */
		interface IScanListener : public IAbstract
		{
			/** Notification of readiness to start the scan
			 *	\param path The path to the file or directory from which to start scanning
			 *				  or an empty string if the requested scans for all drives.
			 *	\param numFiles Number of files to be scanned
			 *	\return true - to begin scanning;
			 *          false - to cancel scanning.
			 */
			virtual bool onFilesystemScanReadyToStart
				( __in const string &path, __in size_t numFiles ) throw() = 0;

			/** Notification about the end of scan
			 */
			virtual void onFilesystemScanCompleted
				( __in const string &path ) throw() = 0;		

			/** Report on progress scans
			 *	\return true - to continue scanning;
			 *			false - to interrupt scanning.
			 */
			virtual bool onFilesystemScanProgress
				( __in size_t numFilesTotal, __in size_t numFilesFound) throw() = 0;		

			/* Notification about detection of the file
			 *	\param pathFileFound The path of the found file
			 */
			virtual void onFilesystemScanFileFound
				( __in const string &pathFileFound ) throw() =  0;

			/* Notification about detection of the directory
			 *	\param pathDirFound The path of the found directory
			 *	\return true - to scan the directory;
			 *			false - to skip the directory.
			 */
			virtual bool onFilesystemScanDirectoryFound
				( __in const string &pathDirFound ) throw() =  0;

			/* Notification about detection of the logical drive
			 *	\param pathDriveFound The path of the found drive
			 *	\return true - to scan the drive;
			 *			false - to skip the drive.
			 */
			virtual bool onFilesystemScanDriveFound
				( __in const string &pathDriveFound ) throw() =  0;
		};
	}
}
