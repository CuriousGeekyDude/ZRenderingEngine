#include "EngineException.hpp"
#include <sstream>

namespace Library
{
	EngineException::EngineException(std::string l_message, HRESULT hr) :
		exception(l_message.c_str()), mHR(hr)
	{
	}

	HRESULT EngineException::HR() const
	{
		return mHR;
	}

	std::wstring EngineException::whatw() const
	{
		std::wstringstream lv_whatw;
		lv_whatw << what();
		return lv_whatw.str();
	}
}