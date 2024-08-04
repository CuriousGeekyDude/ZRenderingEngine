#pragma once


#include <vector>
#include <string>
#include <memory>

namespace Library
{
	class Engine;
	class Mesh;

	class Model
	{

	public:
		Model(Engine*, const std::string&);
		

		//bool HasMaterial() const;
		bool HasMeshes() const;

		Engine* GetEngine();

		const std::vector<std::unique_ptr<Mesh>>& GetMeshes() const;
		//const std::vector<std::unique_ptr<ModelMaterial>>& GetMaterials() const;


	private:
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		Engine* m_engine;
		std::vector<std::unique_ptr<Mesh>> m_meshes{};
		//std::vector<std::unique_ptr<ModelMaterial>> m_materials{};
	};
}