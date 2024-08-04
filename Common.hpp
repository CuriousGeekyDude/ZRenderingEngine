#pragma once 

#include <unknwn.h>

inline void ReleaseObject(IUnknown* l_object)
{
	if (nullptr != l_object) {
		l_object->Release();
		l_object = nullptr;
	}
}

namespace Library
{
	typedef unsigned char Byte;
}