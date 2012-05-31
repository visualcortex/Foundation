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

#include <Dream/Foundation/Logging/Journal.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.Journal"

namespace Dream
{
	namespace Logging
	{
		Journal::Journal(__in const string &name)
			: m_name(name), m_level(Level::All)
		{}

		Journal::~Journal() throw()
		{}

		const string& Journal::getName() const throw()
		{
			return m_name;
		}

		bool Journal::isLoggable(__in Level level)
		{
			return level >= m_level;
		}

		void Journal::setLevel(__in Level value)
		{
			m_level = value;
		}

		Level Journal::getLevel() const throw()
		{
			return m_level;
		}

		void Journal::setFilter(__in std::shared_ptr<IFilter> value)
		{
			m_filter = value;
		}

		std::shared_ptr<IFilter> Journal::getFilter() const throw()
		{
			return m_filter;
		}

		void Journal::addHandler(__in std::shared_ptr<Handler> handler)
		{
			m_handlers.push_back(handler);
		}

		void Journal::removeHandler(__in std::shared_ptr<Handler> handler)
		{
			Handlers::iterator i = std::find
				(m_handlers.begin(), m_handlers.end(), handler);			
		
			if (i != m_handlers.end())
				m_handlers.erase(i);
		}

		const Journal::Handlers& Journal::getHandlers() const throw()
		{
			return m_handlers;
		}

		void Journal::logRecord(__in const Record &record) throw()
		{
			bool isRecordLoggable = false;
			if (record.getLevel() >= m_level)
			{
				isRecordLoggable = m_filter != nullptr ?
					m_filter->isLogRecordLoggable(record) : true;
			}

			if (isRecordLoggable)
			{
				for (Handlers::iterator i = m_handlers.begin(), 
						i_end = m_handlers.end(); i != i_end; ++i)
				{
					(*i)->publish(record);
				}
			}
		}

		void Journal::logMessage
			(__in Level level,
			 __in const string &nameSourceClass, 
			 __in const string &nameSourceFunction,
			 __in const string &message) throw()
		{
			Record record(level, message);

			record.setJournalName(m_name);
			record.setSourceClassName(nameSourceClass);
			record.setSourceFunctionName(nameSourceFunction);

			logRecord(record);
		}

		void Journal::logTrace(__in const string &message) throw()
		{
			logTrace(message, "", "");
		}

		void Journal::logTrace
			(__in const string &message,
			 __in const string &nameSourceClass,
			 __in const string &nameSourceFunction) throw()
		{
			logMessage(Level::Trace, 
					nameSourceClass, nameSourceFunction, message);
		}

		void Journal::logInfo(__in const string &message) throw()
		{
			logInfo(message, "", "");
		}

		void Journal::logInfo
			(__in const string &message,
			 __in const string &nameSourceClass,
			 __in const string &nameSourceFunction) throw()
		{
			logMessage(Level::Info, 
					nameSourceClass, nameSourceFunction, message);
		}

		void Journal::logWarning(__in const string &message) throw()
		{
			logWarning(message, "", "");
		}

		void Journal::logWarning
			(__in const string &message,
			 __in const string &nameSourceClass,
			 __in const string &nameSourceFunction) throw()
		{
			logMessage(Level::Warning, 
					nameSourceClass, nameSourceFunction, message);
		}

		void Journal::logError(__in const string &message) throw()
		{
			logError(message, "", "");
		}

		void Journal::logError
			(__in const string &message,
			 __in const string &nameSourceClass,
			 __in const string &nameSourceFunction) throw()
		{
			logMessage(Level::Error, 
					nameSourceClass, nameSourceFunction, message);
		}

		void Journal::logProgress(__in const string &message) throw()
		{
			logProgress(message, "", "");
		}

		void Journal::logProgress
			(__in const string &message,
			 __in const string &nameSourceClass,
			 __in const string &nameSourceFunction) throw()
		{
			logMessage(Level::Progress, 
					nameSourceClass, nameSourceFunction, message);
		}
	}
}
