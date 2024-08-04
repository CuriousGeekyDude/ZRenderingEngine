#pragma once

#include <DirectXMath.h>
#include <d3d11_1.h>
#include <vector>
#include "EngineException.hpp"

namespace Library
{
	namespace DirectX11Helper
	{

		template<typename T>
		void CreateConstantBuffer(T& l_data, ID3D11Buffer** l_cbBuffer ,ID3D11Device* l_device,
			const unsigned int l_byteWidth, const D3D11_USAGE l_usage,
			const unsigned int l_cpuAccessFlag)
		{
			HRESULT lv_hr{};
			D3D11_BUFFER_DESC lv_constantBufferDesc{};
			ZeroMemory(&lv_constantBufferDesc, sizeof(D3D11_BUFFER_DESC));
			lv_constantBufferDesc.ByteWidth = l_byteWidth;
			lv_constantBufferDesc.Usage = l_usage;
			lv_constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			lv_constantBufferDesc.CPUAccessFlags = l_cpuAccessFlag;


			D3D11_SUBRESOURCE_DATA lv_constantBufferData{};
			ZeroMemory(&lv_constantBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
			lv_constantBufferData.pSysMem = (void*)&l_data;

			lv_hr = l_device->CreateBuffer(&lv_constantBufferDesc, &lv_constantBufferData, l_cbBuffer);

			ThrowIfFailed(lv_hr, "CreateConstantBuffer() failed to create constant buffer.\n");
		}

		template<typename T>
		void CreateImmutableVertexBuffer(ID3D11Device* l_device,const std::vector<T>& l_data
			, ID3D11Buffer** l_vertexBuffer)
		{
			HRESULT lv_hr{};

			D3D11_BUFFER_DESC lv_vertexBufferDesc{};
			ZeroMemory(&lv_vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
			lv_vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			lv_vertexBufferDesc.ByteWidth = l_data.size() * sizeof(T);
			lv_vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

			D3D11_SUBRESOURCE_DATA lv_vertexBufferData{};
			ZeroMemory(&lv_vertexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
			lv_vertexBufferData.pSysMem = (void*)l_data.data();


			lv_hr = l_device->CreateBuffer(&lv_vertexBufferDesc, &lv_vertexBufferData, l_vertexBuffer);

			ThrowIfFailed(lv_hr, "CreateImmutableVertexBuffer() failed to create vertex buffer.\n");
		}

		template<typename T>
		void CreateIndexBuffer(ID3D11Device* l_device, const std::vector<T>& l_data
			, ID3D11Buffer** l_indexBuffer)
		{
			HRESULT lv_hr{};

			D3D11_BUFFER_DESC lv_indexBufferDesc{};
			ZeroMemory(&lv_indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
			lv_indexBufferDesc.ByteWidth = l_data.size() * sizeof(T);
			lv_indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
			lv_indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

			D3D11_SUBRESOURCE_DATA lv_indexBufferData{};
			ZeroMemory(&lv_indexBufferData, sizeof(D3D11_SUBRESOURCE_DATA));
			lv_indexBufferData.pSysMem = (void*)l_data.data();


			lv_hr = l_device->CreateBuffer(&lv_indexBufferDesc, &lv_indexBufferData, l_indexBuffer);

			ThrowIfFailed(lv_hr, "CreateIndexBuffer() failed to create index buffer.\n");
		}

		void CreateInputElementDescription(D3D11_INPUT_ELEMENT_DESC* l_descritpion, const char* l_semanticName,
			unsigned int l_semanticIndex, DXGI_FORMAT l_format, unsigned int l_inputSlot,
			unsigned int l_alignedByteOffset, D3D11_INPUT_CLASSIFICATION l_inputSlotClass = D3D11_INPUT_PER_VERTEX_DATA);

		void DisableShaders(ID3D11DeviceContext* l_context, const std::string& l_shader1 = "HS",
			const std::string& l_shader2 = "DS", const std::string& l_shader3 = "GS");

		void CreateRasterizerState(ID3D11Device*,D3D11_FILL_MODE, D3D11_CULL_MODE, bool l_orientation, 
			ID3D11RasterizerState** l_state);
	}
}