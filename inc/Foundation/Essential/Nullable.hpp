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

#include <Foundation/Essential/Exception.hpp>

namespace Dream
{
	template<class T>
		class nullable
		{
			public:
				nullable() throw()
					: m_value((T)0)
					, m_hasValue(false)
				{}

	            nullable(__in T value) throw()
					: m_value(value)
					, m_hasValue(true)
				{}

			public:
				nullable& operator = (__in T value) throw()
				{
					m_value = value;
					m_hasValue = true;

					return *this;
				}

	        public:
	            void reset() throw()
	            {
	                m_value = 0;
	                m_hasValue = false;
	            }

			public:
				bool hasValue() const throw()
				{
					return m_hasValue;
				}

				T getValue() const
				{
	                preconditions
	                {
	                    if (!m_hasValue)
	                        throw Diagnostics::Exception
	                            ("Dream.Foundation.nullable", DREAM_E_NOT_INITIALIZED);
	                }

					return m_value;
				}

			private:
				T m_value;
				bool m_hasValue;
		};
}
