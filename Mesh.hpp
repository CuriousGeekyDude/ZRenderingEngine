#pragma once

#include <string>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include "Node.hpp"

struct aiMesh;


namespace Library
{

	class ModelMaterial;
	class Model;

	class Mesh
	{
		friend class Model;
		friend class Node;

	public:
		Mesh(Model&,aiMesh&);


		
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

		const std::string& GetName() const;
		const std::vector<DirectX::XMFLOAT3>& GetVertices() const;
		const std::vector<DirectX::XMFLOAT3>& GetNormals() const;
		const std::vector<DirectX::XMFLOAT3>& GetTangents() const;
		const std::vector<DirectX::XMFLOAT3>& GetbiNormals() const;
		const std::vector<std::unique_ptr<std::vector<DirectX::XMFLOAT3>>>& GetTexCoords() const;
		const std::vector<std::unique_ptr<std::vector<DirectX::XMFLOAT4>>>& GetVertexColors() const;

		unsigned int GetFaceCount() const;
		const std::vector<unsigned int>& GetIndices() const;

	private:

		ModelMaterial* m_material{};
		std::string m_name{};
		std::vector<DirectX::XMFLOAT3> m_vertices{};
		std::vector<DirectX::XMFLOAT3> m_normals{};
		std::vector<DirectX::XMFLOAT3> m_tangents{};
		std::vector<DirectX::XMFLOAT3> m_biNormals{};
		std::vector<std::unique_ptr<std::vector<DirectX::XMFLOAT3>>> m_textureCoords{};
		std::vector<std::unique_ptr<std::vector<DirectX::XMFLOAT4>>> m_vertexColors{};
		unsigned int m_faceCount{};
		std::vector<unsigned int> m_indices{};
		
	};
}