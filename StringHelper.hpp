#pragma once

#include <string>
#include <vector>
#include <limits>
#include <functional>
#include <tuple>

namespace Library
{
	namespace StringHelper
	{
		void ToWideString(const std::string& source, std::wstring& dest);
		std::wstring ToWideString(const std::string& source);
		void Totring(const std::wstring& source, std::string& dest);
		std::string ToString(const std::wstring& source);
	};
}