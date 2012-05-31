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

#include <Dream/Foundation/Logging/Level.hpp>

namespace Dream
{
	namespace Logging
	{
		class Record
		{
			public:
				Record() throw();
				Record(__in Level level, __in const string &message) throw();

			public:
				void setLevel(__in Level value) throw();
				Level getLevel() const throw();

				void setTimeStamp(__in uint32 value) throw();
				uint32 getTimeStamp() const throw();

				void setJournalName(__in const string &value) throw();
				const string& getJournalName() const throw();

				void setSourceClassName(__in const string &value) throw();
				const string& getSourceClassName() const throw();

				void setSourceFunctionName(__in const string &value) throw();
				const string& getSourceFunctionName() const throw();

				void setMessage(__in const string &value) throw();
				const string& getMessage() const throw();

			private:
				Level  m_level;
				uint32 m_stampTime;
				string m_nameJournal;
				string m_nameSourceClass;
				string m_nameSourceFunction;
				string m_message;
		};
	}
}
