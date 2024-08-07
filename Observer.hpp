#pragma once

#include <string>

namespace Library
{
	class Observer
	{
	public:
		virtual void Update(float dt,float l_multiplier, const std::string& l_key){}
		virtual void Update(float x, float y){}
	};
}