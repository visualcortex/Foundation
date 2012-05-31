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

#include <Dream/Foundation/Logging/Record.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.Record"

namespace Dream
{
	namespace Logging
	{
		Record::Record() throw()
			: m_level(Level::Trace), m_stampTime(0)
		{}
	
		Record::Record(__in Level level, __in const string &message) throw()
			: m_level(level), m_message(message), m_stampTime(0)
		{}

		void Record::setLevel(__in Level value) throw()
		{
			m_level = value;
		}

		Level Record::getLevel() const throw()
		{
			return m_level;
		}

		void Record::setTimeStamp(__in uint32 value) throw()
		{
			m_stampTime = value;
		}

		uint32 Record::getTimeStamp() const throw()
		{
			return m_stampTime;
		}

		void Record::setSourceClassName(__in const string &value) throw()
		{
			m_nameSourceClass = value;
		}

		const string& Record::getSourceClassName() const throw()
		{
			return m_nameSourceClass;
		}

		void Record::setSourceFunctionName(__in const string &value) throw()
		{
			m_nameSourceFunction = value;
		}

		const string& Record::getSourceFunctionName() const throw()
		{
			return m_nameSourceFunction;
		}

		void Record::setJournalName(__in const string &value) throw()
		{
			m_nameJournal = value;
		}

		const string& Record::getJournalName() const throw()
		{
			return m_nameJournal;
		}

		void Record::setMessage(__in const string &value) throw()
		{
			m_message = value;
		}

		const string& Record::getMessage() const throw()
		{
			return m_message;
		}
	}
}
