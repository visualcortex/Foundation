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

#include <Dream/Foundation/Logging/Handler.hpp>

namespace Dream
{
	namespace Logging
	{
		class Journal
		{
			public:
				Journal(__in const string &name);
				virtual ~Journal() throw();

			public:
				/** Get journal name
				 */
				const string& getName() const throw();

			public:
				/** Check if a message of the given level would actually be logged
				 */
				bool isLoggable(__in Level value);

			public:
				void setLevel(__in Level value);
				Level getLevel() const throw();

				void setFilter(__in std::shared_ptr<IFilter> value);
				std::shared_ptr<IFilter> getFilter() const throw();

			public:
				void addHandler(__in std::shared_ptr<Handler> handler);
				void removeHandler(__in std::shared_ptr<Handler> handler);

				typedef std::list<std::shared_ptr<Handler>> Handlers;
				const Handlers& getHandlers() const throw();
	
			public:
				/** Log record
				 */
				void logRecord
					(__in const Record &record) throw();

				/** Log message
				 */
				void logMessage
					(__in Level level,
					 __in const string &nameSourceClass, 
					 __in const string &nameSourceFunction,
					 __in const string &message) throw();

			public:
				/** Log trace message
				 */
				void logTrace
					(__in const string &message) throw();
				void logTrace
					(__in const string &message,
					 __in const string &nameSourceClass,
					 __in const string &nameSourceFunction) throw();

				/** Log info message
				 */
				void logInfo
					(__in const string &message) throw();
				void logInfo
					(__in const string &message,
					 __in const string &nameSourceClass,
					 __in const string &nameSourceFunction) throw();

				/** Log warning message
				 */
				void logWarning
					(__in const string &message) throw();
				void logWarning
					(__in const string &message,
					 __in const string &nameSourceClass,
					 __in const string &nameSourceFunction) throw();

				/** Log error message
				 */
				void logError
					(__in const string &message) throw();
				void logError
					(__in const string &message,
					 __in const string &nameSourceClass,
					 __in const string &nameSourceFunction) throw();

				/** Log progress message
				 */
				void logProgress
					(__in const string &message) throw();
				void logProgress
					(__in const string &message,
					 __in const string &nameSourceClass,
					 __in const string &nameSourceFunction) throw();

			private:
				Level m_level;
				string m_name;
				Handlers m_handlers;
				std::shared_ptr<IFilter> m_filter;
		};
	}
}
