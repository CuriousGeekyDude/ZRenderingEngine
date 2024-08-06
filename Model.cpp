

#include "Model.hpp"
#include "Engine.hpp"
#include "EngineException.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Library
{


	Model::Model(Engine* l_engine, const std::string& l_fullPath) :m_engine(l_engine)
	{
		Assimp::Importer lv_importer{};

		const aiScene* lv_scene = lv_importer.ReadFile(l_fullPath,
			aiProcess_Triangulate | aiProcess_SortByPType
			| aiProcess_ConvertToLeftHanded | aiProcess_JoinIdenticalVertices);

		if (nullptr == lv_scene) {
			throw EngineException(lv_importer.GetErrorString());
		}

		if (true == lv_scene->HasMaterials()) {
			for (unsigned int i = 0; i < lv_scene->mNumMaterials; ++i) {
				m_materials.emplace_back(std::make_unique<ModelMaterial>(*this, lv_scene->mMaterials[i]));
			}
		}

		if (true == lv_scene->HasMeshes()) {
			for (unsigned int i = 0; i < lv_scene->mNumMeshes; ++i) {
				m_meshes.emplace_back(std::make_unique<Mesh>(*this,*(lv_scene->mMeshes[i])));
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

	bool Model::HasMaterial() const
	{
		return m_materials.size() > 0;
	}
	const std::vector<std::unique_ptr<ModelMaterial>>& Model::GetMaterials() const
	{
		return m_materials;
	}

}