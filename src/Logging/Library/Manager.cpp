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

#include <Dream/Foundation/Logging/Manager.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.Manager"

namespace Dream
{
	namespace Logging
	{
		Manager::Manager() throw()
		{}

		Manager::~Manager() throw()
		{}

		Manager& Manager::Instance() throw()
		{
			static Manager manager;
			return manager;
		}

		void Manager::addJournal(__in std::shared_ptr<Journal> journal)
		{
			string nameJournal = journal->getName();
			if (m_journals.count(nameJournal) == 0)
				m_journals[nameJournal] = journal;
		}

		std::shared_ptr<Journal> Manager::getJournal(__in const string &name)
		{
			if (m_journals.count(name) != 0)
				return m_journals[name];

			throw Exception(SOURCE_CLASS, DREAM_E_INVALID_ARGUMENTS);
		}
	}
}
