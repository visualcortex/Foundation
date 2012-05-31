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

#include <Dream/Foundation/Logging/XmlFormatter.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.XmlFormatter"

namespace Dream
{
	namespace Logging
	{
		string XmlFormatter::formatLogRecord(__in const Record &record)
		{
			string nameJournal = record.getJournalName();
			if (nameJournal.empty())
				nameJournal = "none";

			string nameSourceClass = record.getSourceClassName();
			if (nameSourceClass.empty())
				nameSourceClass = "none";

			string nameSourceFunction = record.getSourceFunctionName();
			if (nameSourceFunction.empty())
				nameSourceFunction = "none";

			string message = record.getMessage();
			if (message.empty())
				message = "none";

			std::ostringstream stream;
			stream << "<Record>"
					<< "\t<Level>" << Convert::ToString(record.getLevel()) << "</Level>\n"
					<< "\t<TimeStamp>" << record.getTimeStamp() << "</TimeStamp>\n"
					<< "\t<JournalName>" << nameJournal << "</JournalName>\n"
					<< "\t<SourceClassName>" << nameSourceClass << "</SourceClassName>\n"
					<< "\t<SourceFunctionName>" << nameSourceFunction << "</SourceFunctionName>\n"
					<< "\t<Message>" << message << "</level>\n"
				   << "</Record>";

			return stream.str();
		}
	}
}
