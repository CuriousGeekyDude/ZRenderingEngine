#pragma once


#include <vector>
#include <string>
#include <memory>
#include "Mesh.hpp"
#include "ModelMaterial.hpp"

namespace Library
{
	class Engine;
	
	class Model
	{

	public:
		Model(Engine*, const std::string&);
		Model(Model&& l_movedModel) noexcept :
			m_engine(l_movedModel.m_engine), m_meshes(std::move(l_movedModel.m_meshes)),
		m_materials(std::move(l_movedModel.m_materials)){}

		bool HasMaterial() const;
		bool HasMeshes() const;

		Engine* GetEngine();

		const std::vector<std::unique_ptr<Mesh>>& GetMeshes() const;
		const std::vector<std::unique_ptr<ModelMaterial>>& GetMaterials() const;


	private:
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;

		Engine* m_engine{};
		std::vector<std::unique_ptr<Mesh>> m_meshes{};
		std::vector<std::unique_ptr<ModelMaterial>> m_materials{};
	};
}