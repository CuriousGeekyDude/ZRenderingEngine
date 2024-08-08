#pragma once 


#include "RTTI.hpp"
#include "InputEventHandler.hpp"

namespace Library
{
	class Engine;
	class EngineTime;
	class ServiceProvider;

	class Component : public RTTI
	{
		RTTI_DECLARATIONS(Component, RTTI);

	public:

		Component(Engine& l_engine);
		Component(const Component& l_component);

		Component& operator=(const Component&) = delete;
		

		virtual ~Component();

		bool IsEnabled() const;
		void SetEnabled(bool l_truthValue);

		virtual void Initialize();
		virtual void Update(const EngineTime&);

	protected:

		bool m_enabled{true};
	};
}