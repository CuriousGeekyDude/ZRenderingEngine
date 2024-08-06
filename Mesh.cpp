

#include "Mesh.hpp"
#include <assimp/scene.h>
#include "Model.hpp"

namespace Library
{
	Mesh::Mesh(Model& l_model,aiMesh& l_aiMesh)
		:m_name(l_aiMesh.mName.C_Str())
	{

		m_material = l_model.GetMaterials()[l_aiMesh.mMaterialIndex].get();

		using namespace DirectX;
		//Vertices
		{
			m_vertices.reserve(l_aiMesh.mNumVertices);
			for (unsigned int i = 0; i < l_aiMesh.mNumVertices; ++i) {
				m_vertices.push_back(XMFLOAT3((const float*)(&l_aiMesh.mVertices[i])));
			}
		}


		//Normals
		{
			if (true == l_aiMesh.HasNormals()) {
				m_normals.reserve(l_aiMesh.mNumVertices);
				for (unsigned int i = 0; i < l_aiMesh.mNumVertices; ++i) {
					m_normals.push_back(XMFLOAT3((const float*)(&l_aiMesh.mNormals[i])));
				}
			}
		}

		//Tangents and Binormals
		{
			if (true == l_aiMesh.HasTangentsAndBitangents()) {
				m_tangents.reserve(l_aiMesh.mNumVertices);
				m_biNormals.reserve(l_aiMesh.mNumVertices);

				for (unsigned int i = 0; i < l_aiMesh.mNumVertices; ++i) {
					m_tangents.push_back(XMFLOAT3((const float*)(&l_aiMesh.mTangents[i])));
					m_biNormals.push_back(XMFLOAT3((const float*)(&l_aiMesh.mBitangents[i])));
				}
			}
		}

		//Texture coordinates
		{
			unsigned int lv_uvChannelCount = l_aiMesh.GetNumUVChannels();

			for (unsigned int i = 0; i < lv_uvChannelCount; ++i) {
				m_textureCoords.emplace_back(std::make_unique<std::vector<XMFLOAT3>>());

				std::vector<XMFLOAT3>* lv_textureCoord = m_textureCoords[i].get();
				lv_textureCoord->reserve(l_aiMesh.mNumVertices);

				auto* lv_aiTextureCoordinates = l_aiMesh.mTextureCoords[i];
				for (unsigned int j = 0; j < l_aiMesh.mNumVertices; ++j) {
					lv_textureCoord->push_back(XMFLOAT3((const float*)(&lv_aiTextureCoordinates[j])));
				}

			}
		}

		//Vertex Colors
		{
			unsigned int lv_colorChannelCount = l_aiMesh.GetNumColorChannels();

			for (unsigned int i = 0; i < lv_colorChannelCount; ++i) {
				
				m_vertexColors.emplace_back(std::make_unique<std::vector<XMFLOAT4>>());
				std::vector<XMFLOAT4>* lv_vertexColors = m_vertexColors[i].get();
				lv_vertexColors->reserve(l_aiMesh.mNumVertices);
				auto* lv_aiVertexColors = l_aiMesh.mColors[i];

				for (unsigned int j = 0; j < l_aiMesh.mNumVertices; ++j) {
					lv_vertexColors->push_back(XMFLOAT4((const float*)(&lv_aiVertexColors[j])));
				}
			}
		}


		//Faces
		{
			if (true == l_aiMesh.HasFaces()) {
				m_faceCount = l_aiMesh.mNumFaces;
				for (unsigned int i = 0; i < m_faceCount; ++i) {
					auto* lv_face = &l_aiMesh.mFaces[i];

					for (unsigned int j = 0; j < lv_face->mNumIndices; ++j) {
						m_indices.push_back(lv_face->mIndices[j]);
					}
				}
			}
		}
	}

	const std::string& Mesh::GetName() const
	{
		return m_name;
	}
	const std::vector<DirectX::XMFLOAT3>& Mesh::GetVertices() const
	{
		return m_vertices;
	}
	const std::vector<DirectX::XMFLOAT3>& Mesh::GetNormals() const
	{
		return m_normals;
	}
	const std::vector<DirectX::XMFLOAT3>& Mesh::GetTangents() const
	{
		return m_tangents;
	}
	const std::vector<DirectX::XMFLOAT3>& Mesh::GetbiNormals() const
	{
		return m_biNormals;
	}
	const std::vector<std::unique_ptr<std::vector<DirectX::XMFLOAT3>>>& Mesh::GetTexCoords() const
	{
		return m_textureCoords;
	}
	const std::vector<std::unique_ptr<std::vector<DirectX::XMFLOAT4>>>& Mesh::GetVertexColors() const
	{
		return m_vertexColors;
	}

	unsigned int Mesh::GetFaceCount() const
	{
		return m_faceCount;
	}
	const std::vector<unsigned int>& Mesh::GetIndices() const
	{
		return m_indices;
	}
}
