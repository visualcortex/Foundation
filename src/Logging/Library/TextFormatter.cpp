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

#include <Dream/Foundation/Logging/TextFormatter.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.TextFormatter"

namespace Dream
{
	namespace Logging
	{
		TextFormatter::TextFormatter(__in bool shouldDumpLogRecordStats)
			: m_shouldDumpLogRecordStats(shouldDumpLogRecordStats)
		{}

		string TextFormatter::formatLogRecord(__in const Record &record)
		{
			string message = record.getMessage();
			if (message.empty())
				message = "none";

			if (record.getLevel() == Level::Progress)
				return message;

			std::ostringstream stream;
			if (m_shouldDumpLogRecordStats)
			{
				string nameJournal = record.getJournalName();
				if (nameJournal.empty())
					nameJournal= "none";

				string nameSourceClass = record.getSourceClassName();
				if (nameSourceClass.empty())
					nameSourceClass = "none";

				string nameSourceFunction = record.getSourceFunctionName();
				if (nameSourceFunction.empty())
					nameSourceFunction = "none";

			
				stream << "# " << record.getTimeStamp() << " "
					   << Convert::ToString(record.getLevel()) << " "			
					   << nameJournal << " "
					   << nameSourceClass << "::"
					   << nameSourceFunction << "\n";
			}
		
			stream << message;
			
			return stream.str();
		}
	}
}
