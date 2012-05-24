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

#include <Foundation/Essential/Types.hpp>

namespace Dream
{
	namespace Diagnostics
	{
		class Exception
		{
			public:
				Exception
					( __in const string &source,
					  __in result_t result ) throw();

				Exception
					( __in const string &source,
					  __in result_t result,
					  __in const string &message ) throw();

	            virtual ~Exception() throw() 
	            {}

			public:
	            /// Returns the description
	            virtual string getDescription() const throw();

				/// Returns the message provided by user
				virtual string getMessage() const throw();

				/// Returns the result code
				virtual result_t getResult() const throw();

				/// Returns the source of exception
				virtual string getSource() const throw();
				
				/// Returns the call stack at the time this exception was generated
				virtual string getCallStack() const throw();

			private:
				result_t m_result;
				string   m_message;
				string   m_source;
		};
	}
}
