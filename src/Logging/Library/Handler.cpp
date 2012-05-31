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

#include <Dream/Foundation/Logging/Handler.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.Handler"

namespace Dream
{
	namespace Logging
	{
		Handler::Handler()
			: m_level(Level::All)
		{}

		Handler::~Handler() throw()
		{}

		void Handler::setLevel(__in Level value)
		{
			m_level = value;
		}

		Level Handler::getLevel() const throw()
		{
			return m_level;
		}

		void Handler::setFilter(__in std::shared_ptr<IFilter> value)
		{
			m_filter = value;
		}

		std::shared_ptr<IFilter> Handler::getFilter() const throw()
		{
			return m_filter;
		}

		void Handler::setFormatter(__in std::shared_ptr<IFormatter> value)
		{
			m_formatter = value;
		}

		std::shared_ptr<IFormatter> Handler::getFormatter() const throw()
		{
			return m_formatter;
		}

		void Handler::setPublisher(__in std::shared_ptr<IPublisher> value)
		{
			m_publisher = value;
		}

		std::shared_ptr<IPublisher> Handler::getPublisher() const throw()
		{
			return m_publisher;
		}

		void Handler::setListener(__in std::shared_ptr<IHandlerListener> value)
		{
			m_listener = value;
		}

		std::shared_ptr<IHandlerListener> Handler::getListener() const throw()
		{
			return m_listener;
		}

		bool Handler::isRecordLoggable(const Record &record) const
		{
			if (record.getLevel() >= m_level)
				return m_filter != nullptr ? 
					m_filter->isLogRecordLoggable(record) : true;

			return false;
		}

		void Handler::publish(__in const Record &record) throw()
		{
			try 
			{
				if (isRecordLoggable(record))
				{
					m_publisher->publishLogMessage
						(record.getLevel(), 
				 			m_formatter->formatLogRecord(record));
				}
			}
			catch (const Exception &exception)
			{
				if (m_listener != nullptr)
					m_listener->onExceptionThrown(exception);
			}
		}
	}
 }
