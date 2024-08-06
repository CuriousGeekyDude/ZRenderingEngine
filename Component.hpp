#pragma once 


#include "RTTI.hpp"

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
		Component(const Component& l_component) : m_serviceProvider(l_component.m_serviceProvider)
		{
			m_enabled = l_component.m_enabled;
		}

		Component& operator=(const Component&) = delete;
		

		virtual ~Component();

		bool IsEnabled() const;
		void SetEnabled(bool l_truthValue);

		virtual void Initialize();
		virtual void Update(const EngineTime&);

	protected:

		bool m_enabled{true};
		const ServiceProvider& m_serviceProvider;

	};
}