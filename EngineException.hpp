#pragma once

#include <Windows.h>
#include <exception>
#include <string>

namespace Library
{
	class EngineException : public std::exception
	{
	public:
		EngineException(std::string l_message, HRESULT hr = S_OK);

		HRESULT HR() const;
		std::wstring whatw() const;

	private:
		HRESULT mHR;
	};

	inline void ThrowIfFailed(HRESULT hr, const std::string& l_message)
	{
		if (FAILED(hr))
		{
			throw EngineException(l_message, hr);
		}
	}
}