

#include "Model.hpp"
#include "Mesh.hpp"
#include "Engine.hpp"
#include "EngineException.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Library
{
	Model::Model(Engine* l_engine, const std::string& l_fullPath)
	{
		Assimp::Importer lv_importer{};

		const aiScene* lv_scene = lv_importer.ReadFile(l_fullPath,
			aiProcess_Triangulate | aiProcess_SortByPType
			| aiProcess_ConvertToLeftHanded | aiProcess_JoinIdenticalVertices);

		if (nullptr == lv_scene) {
			throw EngineException(lv_importer.GetErrorString());
		}

		if (true == lv_scene->HasMeshes()) {
			for (unsigned int i = 0; i < lv_scene->mNumMeshes; ++i) {
				m_meshes.emplace_back(std::make_unique<Mesh>(*(lv_scene->mMeshes[i])));
			}
		}
	}

	bool Model::HasMeshes() const
	{
		return m_meshes.size() > 0;
	}

	Engine* Model::GetEngine()
	{
		return m_engine;
	}

	const std::vector<std::unique_ptr<Mesh>>& Model::GetMeshes() const
	{
		return m_meshes;
	}
}