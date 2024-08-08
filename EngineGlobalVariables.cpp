#include "EngineGlobalVariables.hpp"


namespace EngineGlobalVariables
{
	std::wstring lv_spriteFontPath{ L"Content/SpriteFonts/" };
	std::string lv_modelsFolderPath{ "Content/3DModels/gltf2.0/" };
	std::string lv_modelNamesFile{ "ModelNames.txt" };

	bool lv_UpdatePerFrameConstantBuffers = true;
	bool lv_InitializePerFrameConstantBuffers = true;
}