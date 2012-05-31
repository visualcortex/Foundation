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
		class FunctionMarker : Noncopyable
		{
			public:
				FunctionMarker
					(__in Journal &journal, 
					 __in const string &nameSourceClass,
					 __in const string &nameSourceFunction) throw();

				~FunctionMarker() throw();

			public:
				void markHappyEnd() throw();

			private:
				Journal &m_journal;			
				string m_nameSourceClass;
				string m_nameSourceFunction;
				bool m_isHappyEnd;
		};
	}
}
