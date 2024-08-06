#include "StringHelper.hpp"
#include <locale>
#include <codecvt>

using namespace std;

namespace Library
{
	namespace StringHelper
	{
#pragma warning(push)
#pragma warning(disable: 4996)
		void ToWideString(const string& source, wstring& dest)
		{
			dest = wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(source);
		}

		wstring ToWideString(const string& source)
		{
			return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(source);
		}

		void Totring(const wstring& source, string& dest)
		{
			dest = wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(source);
		}

		string ToString(const wstring& source)
		{
			return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(source);
		}
#pragma warning(pop)
	}
}