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

#include "../Precompiled.hpp"

#include <Dream/Foundation/IO/Redirection.hpp>
#include <Dream/Foundation/IO/Exception.hpp>

#include "Platform.hpp"

#define SOURCE_CLASS "Dream.Foundation.IO.Redirection"

namespace Dream
{
	namespace IO
	{
		Redirection::Redirection()
			: m_shouldRevert(false),
			  m_stateToRevert(nullptr)
		{}

		Redirection::~Redirection() throw()
		{
			revert();	
		}

		void Redirection::disable()
		{
			if (!m_shouldRevert)
			{
				if (Platform::Wow64DisableWow64FsRedirection(&m_stateToRevert) != 0)
					m_shouldRevert = true;
				else
					throw Exception(SOURCE_CLASS, System::Environment::GetLastError());
			}
		}
	
		void Redirection::revert() throw()
		{
			if (m_shouldRevert)
			{
				Platform::Wow64RevertWow64FsRedirection(m_stateToRevert);
				m_shouldRevert = false;
			}
		}
	}
}
