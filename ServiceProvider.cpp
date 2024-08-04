

#include "ServiceProvider.hpp"

namespace Library
{
	ServiceProvider::ServiceProvider() = default;

	void ServiceProvider::AddService(std::uint32_t l_key, void* l_service)
	{
		m_servicesComponents.insert(std::pair<std::uint32_t, void*>(l_key, l_service));
	}

	void ServiceProvider::AddService(std::string l_nameCB, ID3D11Buffer* l_cb)
	{
		m_servicesRarelyChangedConstantBuffers.insert(std::pair<std::string, ID3D11Buffer*>(l_nameCB, l_cb));
	}

	void ServiceProvider::RemoveService(std::uint32_t l_key)
	{
		m_servicesComponents.erase(l_key);
	}

	void ServiceProvider::RemoveService(const std::string& l_nameCB)
	{
		m_servicesRarelyChangedConstantBuffers.erase(l_nameCB);
	}

	const ID3D11Buffer* ServiceProvider::GetService(const std::string& l_nameCB) const
	{
		std::map<std::string, ID3D11Buffer*>::const_iterator lv_service =
			m_servicesRarelyChangedConstantBuffers.find(l_nameCB);

		return lv_service != m_servicesRarelyChangedConstantBuffers.end() ? lv_service->second : nullptr;
	}

	const void* ServiceProvider::GetService(std::uint32_t l_key) const
	{
		std::map<std::uint32_t,void*>::const_iterator lv_service = m_servicesComponents.find(l_key);

		return lv_service != m_servicesComponents.end() ? lv_service->second : nullptr;
	}
}