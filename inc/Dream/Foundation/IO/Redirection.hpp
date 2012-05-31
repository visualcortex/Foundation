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

#include <Dream/Foundation/Essential.hpp>

namespace Dream
{
	namespace IO
	{
		class Redirection
		{
			public:
				Redirection() throw();
				~Redirection() throw();

			public:
				void disable();
				void revert() throw();

			private:
				bool m_shouldRevert;
				void *m_stateToRevert;
		};
	}
}
