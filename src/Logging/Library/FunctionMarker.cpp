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

#include <Dream/Foundation/Logging/FunctionMarker.hpp>
#include <Dream/Foundation/Logging/Exception.hpp>

#define SOURCE_CLASS "Dream.Foundation.Logging.FunctionMarker"

namespace Dream
{
	namespace Logging
	{
		FunctionMarker::FunctionMarker
			(__in Journal &journal, 
			 __in const string &nameSourceClass,
			 __in const string &nameSourceFunction) throw()
			: m_journal(journal), 
			  m_nameSourceClass(nameSourceClass), 
			  m_nameSourceFunction(nameSourceFunction),
			  m_isHappyEnd(false)
		{
			m_journal.logMessage(Level::Trace, 
				m_nameSourceClass, m_nameSourceFunction, "Function entry");
		}

		FunctionMarker::~FunctionMarker() throw()
		{
			m_journal.logMessage(m_isHappyEnd ? Level::Trace : Level::Warning, 
				m_nameSourceClass, m_nameSourceFunction, "Function return");
		}

		void FunctionMarker::markHappyEnd() throw()
		{
			m_isHappyEnd = true;
		}
	}
}
