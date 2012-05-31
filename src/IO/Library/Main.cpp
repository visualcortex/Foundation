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

#include <Dream/Foundation/IO.hpp>

namespace Dream
{ 
	namespace Convert
	{
		string ToString(__in IO::FileAccessRights value)
		{
			switch (value)
			{
				case IO::FileAccessRights::Read:      return "Read";
				case IO::FileAccessRights::Write:     return "Write";
				case IO::FileAccessRights::ReadWrite: return "ReadWrite";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}

		string ToString(__in IO::FileMapAccessRights value)
		{
			switch (value)
			{
				case IO::FileMapAccessRights::Read:             return "Read";
				case IO::FileMapAccessRights::ReadWrite:        return "ReadWrite";
				case IO::FileMapAccessRights::ExecuteRead:      return "ExecuteRead";
				case IO::FileMapAccessRights::ExecuteReadWrite: return "ExecuteReadWrite";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}

		string ToString(__in IO::FileViewAccessRights value)
		{
			switch (value)
			{
				case IO::FileViewAccessRights::Read:      return "Read";
				case IO::FileViewAccessRights::Write:     return "Write";
				case IO::FileViewAccessRights::ReadWrite: return "ReadWrite";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}

		string ToString(__in IO::FileFeatures value)
		{
			std::ostringstream stream;

			if (value & IO::FileFeature::Archive)      stream << "Archive|";
			if (value & IO::FileFeature::Compressed)   stream << "Compressed|";
			if (value & IO::FileFeature::Directory)    stream << "Directory|";
			if (value & IO::FileFeature::Encrypted)    stream << "Encrypted|";
			if (value & IO::FileFeature::Hidden)       stream << "Hidden|";
			if (value & IO::FileFeature::Normal)       stream << "Normal|";
			if (value & IO::FileFeature::Offline)      stream << "Offline|";
			if (value & IO::FileFeature::Readonly)     stream << "Readonly|";
			if (value & IO::FileFeature::ReparsePoint) stream << "ReparsePoint|";
			if (value & IO::FileFeature::SparseFile)   stream << "SparseFile|";
			if (value & IO::FileFeature::System)       stream << "System|";
			if (value & IO::FileFeature::Temporary)    stream << "Temporary|";
			if (value & IO::FileFeature::Virtual)      stream << "Virtual|";

			return stream.str();
		}

		string ToString(__in IO::FileOpenMode value)
		{
			switch (value)
			{
				case IO::FileOpenMode::Create:       return "Create";
				case IO::FileOpenMode::CreateNew:    return "CreateNew";
				case IO::FileOpenMode::Open:         return "Open";
				case IO::FileOpenMode::OpenExisting: return "OpenExisting";
				case IO::FileOpenMode::Append:       return "Append";
				case IO::FileOpenMode::Truncate:     return "Truncate";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}

		string ToString(__in IO::FileSeekMode value)
		{
			switch (value)
			{
				case IO::FileSeekMode::Begin:		return "Begin";
				case IO::FileSeekMode::Current:		return "Current";
				case IO::FileSeekMode::End:			return "End";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}

		string ToString(__in IO::FileShareMode value)
		{
			switch (value)
			{
				case IO::FileShareMode::None:      return "None";
				case IO::FileShareMode::Read:      return "Read";
				case IO::FileShareMode::Write:     return "Write";
				case IO::FileShareMode::ReadWrite: return "ReadWrite";
				case IO::FileShareMode::Delete:    return "Delete";
				default:
					DREAM_NODEFAULT;
			}

			return "";
		}
	}
}
