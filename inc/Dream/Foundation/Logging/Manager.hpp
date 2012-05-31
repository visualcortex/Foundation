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

#include <Dream/Foundation/Logging/Journal.hpp>

namespace Dream
{
	namespace Logging
	{
		class Manager
		{
			public:
				Manager() throw();
				~Manager() throw();

			public:
				static Manager& Instance() throw();

			public:
				void addJournal(__in std::shared_ptr<Journal> journal);
				std::shared_ptr<Journal> getJournal(__in const string &name);

			private:
				typedef std::map<string, std::shared_ptr<Journal>> JournalMap;
				JournalMap m_journals;
		};
	}
}
