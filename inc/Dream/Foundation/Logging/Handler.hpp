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

#include <Dream/Foundation/Logging/Filter.hpp>
#include <Dream/Foundation/Logging/Formatter.hpp>
#include <Dream/Foundation/Logging/HandlerListener.hpp>
#include <Dream/Foundation/Logging/Publisher.hpp>
#include <Dream/Foundation/Logging/Record.hpp>

namespace Dream
{
	namespace Logging
	{
		/** Provides support for processing log records
		 */
		class Handler
		{
			public:
				Handler();
				virtual ~Handler() throw();

			public:
				void setLevel(__in Level level);
				Level getLevel() const throw();

				void setFilter(__in std::shared_ptr<IFilter> value);
				std::shared_ptr<IFilter> getFilter() const throw();

				void setFormatter(__in std::shared_ptr<IFormatter> value);
				std::shared_ptr<IFormatter> getFormatter() const throw();

				void setPublisher(__in std::shared_ptr<IPublisher> value);
				std::shared_ptr<IPublisher> getPublisher() const throw();

				void setListener(__in std::shared_ptr<IHandlerListener> value);
				std::shared_ptr<IHandlerListener> getListener() const throw();

			public:
				/** Check if this handler would actually log a given record
				 */
				bool isRecordLoggable(const Record &record) const;

			public:
				/** Publish a record
				 */
				virtual void publish(__in const Record &record) throw();

			private:
				Level m_level;
				std::shared_ptr<IFilter> m_filter;
				std::shared_ptr<IFormatter> m_formatter;
				std::shared_ptr<IPublisher> m_publisher;
				std::shared_ptr<IHandlerListener> m_listener;
		};
	}
}
