
#pragma comment(lib,"d3dcompiler.lib")

#include "Node.hpp"
#include <array>
#include <vector>
#include "EngineException.hpp"
#include <d3dcompiler.h>
#include "Camera.hpp"
#include "DirectX11Helper.hpp"
#include "Mesh.hpp"
#include "Engine.hpp"

namespace Library
{
	Library::RTTI_DEFINITIONS(Node);

	Node::Node(Library::Engine& l_engine, std::shared_ptr<Library::Camera>& l_camera, const DirectX::XMFLOAT3&l_worldTransformation,
		Mesh* l_mesh) :
		DrawableComponent(l_engine, l_camera), m_worldTransformation(l_worldTransformation), m_mesh(l_mesh) {}
	Node::Node(Library::Engine& l_engine, const DirectX::XMFLOAT3& l_worldTransformation, Mesh* l_mesh)
		: DrawableComponent(l_engine), m_worldTransformation(l_worldTransformation), m_mesh(l_mesh) {}

	void Node::Initialize()
	{
		using namespace DirectX;
		using namespace Library;
		using namespace Library::DirectX11Helper;

		HRESULT lv_hr{};
		
		std::vector<XMFLOAT3> lv_vertices{};
		std::vector<unsigned int> lv_indices{};

		lv_vertices.reserve(m_mesh->m_vertices.size());
		lv_indices.reserve(m_mesh->m_indices.size());

		for (unsigned int i = 0; i < m_mesh->m_vertices.size(); ++i) {
			lv_vertices.push_back(m_mesh->m_vertices[i]);
		}

		for (unsigned int i = 0; i < m_mesh->m_indices.size(); ++i) {
			lv_indices.push_back(m_mesh->m_indices[i]);
		}



		//Vertex buffer created
		{
			CreateImmutableVertexBuffer<XMFLOAT3>(m_device, lv_vertices, &m_vertexBuffer);
		}

		//Index buffer created
		{
			CreateIndexBuffer<unsigned int>(m_device, lv_indices, &m_indexBuffer);
	
		}


		//Compiling shaders and creating shader objects
		{
			CreateVsPsShaders(L"C:/Users/farhan/source/repos/Z/ZRenderingEngine/Content/Shaders/Triangle.hlsl");
		}


		//Creating input layout object
		{
			D3D11_INPUT_ELEMENT_DESC lv_inputDesc{};
			CreateInputElementDescription(&lv_inputDesc, "POSITIONL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
				0, 0, D3D11_INPUT_PER_VERTEX_DATA);

			lv_hr = m_device->CreateInputLayout(&lv_inputDesc, 1, m_vsShaderBytecode->GetBufferPointer(), m_vsShaderBytecode->GetBufferSize(), &m_inputLayoutObject);
			ThrowIfFailed(lv_hr, "CreateInputLayout() failed.\n");

		}

		//Create common rasterizer states
		{
			CreateRasterizerState(D3D11_FILL_WIREFRAME, D3D11_CULL_BACK, false);
			CreateRasterizerState(D3D11_FILL_SOLID, D3D11_CULL_BACK, false);
		}

	}

	void Node::SetWireframe(bool l_enableWireframe)
	{
		m_wireframeEnabled = l_enableWireframe;
	}

	void Node::Draw(const Library::EngineTime& l_engineTime)
	{
		using namespace DirectX;
		using namespace Library::DirectX11Helper;
		HRESULT lv_hr{};

		//Setup IA Stage
		{
			UINT lv_stride{ sizeof(XMFLOAT3) }, lv_offset{ 0 };

			m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &lv_stride, &lv_offset);
			m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, lv_offset);
			m_deviceContext->IASetInputLayout(m_inputLayoutObject);
			m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		//Setup vertex shader stage
		{
			m_deviceContext->VSSetShader(m_vsShader, nullptr, 0);
			m_deviceContext->VSSetConstantBuffers(0, 1,
				&m_updatePerFrameConstantBuffer);
		}

		DisableShaders(m_deviceContext);

		//Setup pixel shader stage
		{
			m_deviceContext->PSSetShader(m_psShader, nullptr, 0);
			m_deviceContext->PSSetConstantBuffers(0, 1,
				&m_updatePerFrameConstantBuffer);
		}
		
		if (true == m_wireframeEnabled) {
			m_deviceContext->RSSetState(m_rasterizerStates["wireframe"]);
		}
		else {
			m_deviceContext->RSSetState(m_rasterizerStates["solid"]);
		}

		m_deviceContext->DrawIndexedInstanced(m_mesh->m_indices.size(), 1, 0, 0, 0);
	}

	void Node::CreateVsPsShaders(const std::wstring& l_fullpathFile)
	{
		using namespace Library;

		HRESULT lv_hr{};

		lv_hr = D3DCompileFromFile(l_fullpathFile.c_str(),
			nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &m_vsShaderBytecode, nullptr);

		ThrowIfFailed(lv_hr, "Vertex shader failed to compile.");

		lv_hr = D3DCompileFromFile(l_fullpathFile.c_str(),
			nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, 0, &m_psShaderBytecode, nullptr);

		ThrowIfFailed(lv_hr, "Pixel shader failed to compile.");

		lv_hr = m_device->CreateVertexShader(m_vsShaderBytecode->GetBufferPointer(), m_vsShaderBytecode->GetBufferSize(),
			nullptr, &m_vsShader);
		ThrowIfFailed(lv_hr, "CreateVertexShader() failed.");

		lv_hr = m_device->CreatePixelShader(m_psShaderBytecode->GetBufferPointer(),
			m_psShaderBytecode->GetBufferSize(), nullptr, &m_psShader);
		ThrowIfFailed(lv_hr, "CreatePixelShader() failed.");

	}


	void Node::CreateRasterizerState(D3D11_FILL_MODE l_fillMode, D3D11_CULL_MODE l_cullMode, bool l_orientation)
	{
		using namespace Library;

		ID3D11RasterizerState* lv_rasterState{};
		DirectX11Helper::CreateRasterizerState(m_device, l_fillMode, l_cullMode, l_orientation, &lv_rasterState);

		if (l_fillMode == D3D11_FILL_SOLID) {
			m_rasterizerStates.insert(std::pair<std::string, ID3D11RasterizerState*>("solid", lv_rasterState));
		}
		else {
			m_rasterizerStates.insert(std::pair<std::string, ID3D11RasterizerState*>("wireframe", lv_rasterState));
		}
	}

	void Node::SetPerFrameConstantBuffer(ID3D11Buffer* l_cb) { m_updatePerFrameConstantBuffer = l_cb; }

}