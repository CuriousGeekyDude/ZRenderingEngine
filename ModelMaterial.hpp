#pragma once


#include <string>
#include <map>
#include <vector>
#include <memory>

struct aiMaterial;

namespace Library
{
	enum TextureType
	{
		TextureTypeDiffuse = 0,
		TextureTypeSpecularMap,
		TextureTypeAmbient,
		TextureTypeEmissive,
		TextureTypeHeightMap,
		TextureTypeNormalMap,
		TextureTypeSpecularPowerMap,
		TextureTypeDisplacementMap,
		TextureTypeLightMap,
		TextureTypeEnd
	};

	class Model;

	class ModelMaterial
	{
		friend class Model;

	public:
		ModelMaterial(Model& l_model);
		ModelMaterial(Model& l_model, aiMaterial* l_material);

		ModelMaterial& operator=(const ModelMaterial&) = delete;


		Model* GetModel();
		const std::string& GetName() const;
		const std::map<TextureType, std::unique_ptr<std::vector<std::wstring>>>&
			GetTextures() const;



	private:

		static void InitializeTextureTypeMappings();
		static std::map<TextureType, unsigned int> lv_textureTypeMappings;


		Model* m_model{};
		std::string m_name{};
		std::map<TextureType, std::unique_ptr<std::vector<std::wstring>>> m_textures{};
	};
}