#pragma once

#include "DrawableComponent.hpp"
#include <DirectXMath.h>
#include "RTTI.hpp"
#include <d3d11_1.h>
#include "MainPassConstantBuffer.hpp"
#include <map>

namespace Library
{
	class Engine;
	class Camera;
	class EngineTime;
}


namespace Library
{
	class Mesh;

	class Node : public Library::DrawableComponent
	{
		RTTI_DECLARATIONS(Node, DrawableComponent);

	public:
		Node(Library::Engine&, Library::Camera&, const DirectX::XMFLOAT3&, Mesh* l_mesh);
		Node(Library::Engine&, const DirectX::XMFLOAT3&, Mesh* l_mesh);

		void SetWireframe(bool);

		virtual void Initialize() override;
		virtual void Update(const Library::EngineTime&) override {};
		virtual void Draw(const Library::EngineTime&) override;

	protected:
		void CreateRasterizerState(D3D11_FILL_MODE, D3D11_CULL_MODE, bool l_orientation);

	private:

		void CreateVsPsShaders(const std::wstring& l_fullpathFile);


		DirectX::XMFLOAT3 m_worldTransformation{};

		ID3D11Buffer* m_vertexBuffer{};
		ID3D11Buffer* m_indexBuffer{};


		ID3DBlob* m_vsShaderBytecode{};
		ID3DBlob* m_psShaderBytecode{};
		ID3DBlob* m_hsShaderBytecode{};
		ID3DBlob* m_dsShaderBytecode{};
		ID3DBlob* m_gsShaderBytecode{};

		ID3D11VertexShader* m_vsShader{};
		ID3D11PixelShader* m_psShader{};
		ID3D11HullShader* m_hsShader{};
		ID3D11DomainShader* m_dsShader{};
		ID3D11GeometryShader* m_gsShader{};

		std::map<std::string, ID3D11RasterizerState*> m_rasterizerStates{};

		std::string m_name{};
		Mesh* m_mesh{};

		bool m_wireframeEnabled{true};

		ID3D11InputLayout* m_inputLayoutObject{};
	};
}