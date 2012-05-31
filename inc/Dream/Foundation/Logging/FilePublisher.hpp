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

#include <Dream/Foundation/Logging/Publisher.hpp>
#include <Dream/Foundation/IO.hpp>

namespace Dream
{
	namespace Logging
	{
		/** Provides support for publishing log messages to file
		 */
		class FilePublisher : public IPublisher
		{
			public:
				FilePublisher(__in const string &pathFile);
				~FilePublisher() throw();

			public:
				virtual void publishLogMessage
					(__in Level level,
					 __in const string &message) override;

			private:
				IO::FileStream m_stream;			
		};
	}
}
