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

#include <Dream/Foundation/IO/Scan.hpp>
#include <Dream/Foundation/IO/Directory.hpp>
#include <Dream/Foundation/IO/Exception.hpp>
#include <Dream/Foundation/IO/File.hpp>

#define SOURCE_CLASS "Dream.Foundation.IO.Scan"

namespace Dream
{
	namespace IO
	{
		/**************************************************************************
		 * Internal
		 *************************************************************************/

		namespace 
		{
			/** Параметры сканирования
			 */
			struct ScanParams
			{
				string filter;
				bool isRecursive;
				std::shared_ptr<IScanListener> listener;
				size_t numFilesTotal;
				size_t numFilesFound;
			};

			/** Сканирование директории
			 *	\param pathBaseDirectory Путь к директории, с которой начать сканирование
			 *	\param paramsScan Параметры сканирования
			 *	\param listenerScan Прослушиватель процесса сканирования
			 *	\param argsScanListener Аргументы прослушивателя процесса сканирования
			 */
			void ScanDirectory
				( __in const string &pathParentDir,
				  __in ScanParams &params)
			{
				string pattern = pathParentDir + "\\*.*";

				struct _finddata_t file;
				intptr_t hFile = _findfirst(pattern.c_str(), &file);
				if (hFile != -1L )
				{
					do
					{
						if (_stricmp(file.name, ".") == 0 || _stricmp(file.name, "..") == 0)
							continue;

						string pathFile = (pathParentDir + "\\") + file.name;
						if ((file.attrib & _A_SUBDIR) == 0)
						{
							params.numFilesFound++;
							params.listener->onFilesystemScanProgress
								(params.numFilesTotal, params.numFilesFound);

							params.listener->onFilesystemScanFileFound(pathFile);
						}
						else if (params.isRecursive)
						{
							if (params.listener->onFilesystemScanDirectoryFound(pathFile))
								ScanDirectory(pathFile, params);
						}
					}
					while (_findnext(hFile, &file) == 0);
			
					_findclose(hFile);
				}
			}
		}

		/**************************************************************************
		 * Implementation
		 *************************************************************************/

		Scan::Scan()
			: isRecursive(false)
		{}

		void Scan::run()
		{
			preconditions
			{
				DREAM_ASSERT(listener != nullptr);
				DREAM_ASSERT(!path.empty());
			}

			ScanParams params;

			params.filter = filter;
			params.listener = listener;
			params.isRecursive = isRecursive;

			if (path == "${SYSTEM}")
			{
				StringArray drives = System::Environment::GetLogicalDrives();
				
				string msg;
				for (size_t i = 0; i < drives.size(); i++)
					msg += drives[i] + "; ";
				
				if (listener->onFilesystemScanReadyToStart(msg, (size_t)-1))
				{
					for (size_t i = 0; i < drives.size(); i++)
					{
						if (listener->onFilesystemScanDriveFound(drives[i]))
							ScanDirectory(drives[i], params);
					}
				}
				
				listener->onFilesystemScanCompleted(path);
			}
			else
			{
				if (File::GetFeatures(path) & FileFeature::Directory)
				{
					size_t numFiles = Directory::GetNumFiles(path, isRecursive);
					if (listener->onFilesystemScanReadyToStart(path, numFiles))
					{
						params.numFilesTotal = numFiles;
						params.numFilesFound = 0;

						if (listener->onFilesystemScanDirectoryFound(path))
							ScanDirectory(path, params);
					}

					listener->onFilesystemScanCompleted(path);
				}
				else
				{
					if (listener->onFilesystemScanReadyToStart(path, 1))
						listener->onFilesystemScanFileFound(path);

					listener->onFilesystemScanCompleted(path);
				}
			}
		}
	}
}
