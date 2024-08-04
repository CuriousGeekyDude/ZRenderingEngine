#pragma once

#include <map>
#include <cstdint>
#include <string>
#include <d3d11_1.h>

namespace Library
{
	class ServiceProvider
	{
	public:
		ServiceProvider();

		void AddService(std::uint32_t, void*);
		void AddService(std::string, ID3D11Buffer*);
		void RemoveService(std::uint32_t);
		void RemoveService(const std::string&);
		const ID3D11Buffer* GetService(const std::string&) const;
		const void* GetService(std::uint32_t) const;

	private:
		std::map<std::uint32_t, void*> m_servicesComponents{};
		std::map<std::string, ID3D11Buffer*> m_servicesRarelyChangedConstantBuffers{};
		
	};
}