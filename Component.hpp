#pragma once 


#include "RTTI.hpp"

namespace Library
{
	class Engine;
	class EngineTime;

	class Component : public RTTI
	{
		RTTI_DECLARATIONS(Component, RTTI);

	public:

		Component(Engine& l_engine);
		Component();
		Component(const Component&) = delete;
		Component& operator=(const Component&) = delete;

		virtual ~Component();

		Engine* GetEngine();
		bool IsEnabled() const;
		void SetEnabled(bool l_truthValue);
		void SetEngine(Engine& l_engine);

		virtual void Initialize();
		virtual void Update(const EngineTime&);

	protected:
		Engine* m_engine{};
		bool m_enabled{true};
	};
}