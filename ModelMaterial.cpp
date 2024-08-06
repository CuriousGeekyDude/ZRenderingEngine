

#include "ModelMaterial.hpp"
#include "Model.hpp"
#include <assimp/scene.h>
#include "StringHelper.hpp"

namespace Library
{
	ModelMaterial::ModelMaterial(Model& l_model)
		:m_model(&l_model)
	{
		InitializeTextureTypeMappings();
	}

	Model* ModelMaterial::GetModel()
	{
		return m_model;
	}
	const std::string& ModelMaterial::GetName() const
	{
		return m_name;
	}
	const std::map<TextureType, std::unique_ptr<std::vector<std::wstring>>>&
		ModelMaterial::GetTextures() const
	{
		return m_textures;
	}

	ModelMaterial::ModelMaterial(Model& l_model, aiMaterial* l_material)
		:m_model(&l_model)
	{
		InitializeTextureTypeMappings();

		aiString lv_name;

		l_material->Get(AI_MATKEY_NAME, lv_name);
		m_name = lv_name.C_Str();

		for (TextureType lv_textureType = TextureType::TextureTypeDiffuse; lv_textureType < TextureType::TextureTypeEnd; lv_textureType=(TextureType)(lv_textureType+1)) {
			auto lv_mappedTextureType = (aiTextureType)(lv_textureTypeMappings[lv_textureType]);

			unsigned int lv_textureCount = l_material->GetTextureCount(lv_mappedTextureType);

			if (0 < lv_textureCount) {
				m_textures.emplace(lv_textureType, std::make_unique<std::vector<std::wstring>>());
				auto lv_texture = m_textures[lv_textureType].get();
				lv_texture->reserve(lv_textureCount);

				for (unsigned int lv_textureIndex = 0; lv_textureIndex < lv_textureCount; ++lv_textureIndex) {
					aiString lv_path{};
					if (AI_SUCCESS == l_material->GetTexture(lv_mappedTextureType, lv_textureIndex, &lv_path)) {
						std::wstring lv_wPath{};
						StringHelper::ToWideString(lv_path.C_Str(), lv_wPath);
						lv_texture->push_back(lv_wPath);
					}
				}

			}

		}
	}


	void ModelMaterial::InitializeTextureTypeMappings()
	{
		if (TextureType::TextureTypeEnd != lv_textureTypeMappings.size()) {
			lv_textureTypeMappings[TextureType::TextureTypeDiffuse] = aiTextureType_DIFFUSE;
			lv_textureTypeMappings[TextureType::TextureTypeSpecularMap] = aiTextureType_SPECULAR;
			lv_textureTypeMappings[TextureType::TextureTypeAmbient] = aiTextureType_AMBIENT;
			lv_textureTypeMappings[TextureType::TextureTypeHeightMap] = aiTextureType_HEIGHT;
			lv_textureTypeMappings[TextureType::TextureTypeNormalMap] = aiTextureType_NORMALS;
			lv_textureTypeMappings[TextureType::TextureTypeSpecularPowerMap] = aiTextureType_SHININESS;
			lv_textureTypeMappings[TextureType::TextureTypeDisplacementMap] = aiTextureType_DISPLACEMENT;
			lv_textureTypeMappings[TextureType::TextureTypeLightMap] = aiTextureType_LIGHTMAP;
		}
	}

	std::map<TextureType, unsigned int> ModelMaterial::lv_textureTypeMappings{};
}

