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

#include <Dream/Foundation/Essential/Exception.hpp>
#include <Dream/Foundation/Essential/Results.hpp>

namespace Dream
{
	namespace Diagnostics
	{ 
		Exception::Exception
			( __in const string &source, 
			  __in result_t result ) throw()
			  : m_source(source), 
			    m_result(result), 
			    m_message("")
		{}

		Exception::Exception
			( __in const string &source,
			  __in result_t result,
			  __in const string &message ) throw()
			  : m_source(source), 
			    m_result(result), 
				m_message(message)
		{}

	    string Exception::getDescription() const throw()
	    {
	        return Results::ToString(m_result);
	    }

		string Exception::getMessage() const throw()
		{
			return m_message;
		}

		result_t Exception::getResult() const throw()
		{
			return m_result;
		}

		string Exception::getSource() const throw()
		{
			return m_source;
		}

		string Exception::getCallStack() const throw()
		{
			return "";
		}
	}
}
