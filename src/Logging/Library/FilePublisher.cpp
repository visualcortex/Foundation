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

#include "Precompiled.hpp"

#include <Dream/Foundation/Logging/FilePublisher.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.FilePublisher"

namespace Dream
{
	namespace Logging
	{
		FilePublisher::FilePublisher(__in const string &pathFile)
			: m_stream(pathFile, 
				IO::FileOpenMode::Create, 
				IO::FileAccessRights::Write, 
				IO::FileShareMode::Read)
		{
			// const uint16 BOM = 0xFEFF;
			// m_stream.write((const byte*)&BOM, 2);
		}

		FilePublisher::~FilePublisher() throw()
		{}

		void FilePublisher::publishLogMessage
			(__in Level level, __in const string &message)
		{
			if (level != Level::Progress)
			{
				m_stream.write((const byte*)message.c_str(), 
						message.size() * sizeof(string::value_type));
				m_stream.write((const byte*)"\n", sizeof(char));
			
				// TODO: Flush stream on error
			}
		}
	}
}
