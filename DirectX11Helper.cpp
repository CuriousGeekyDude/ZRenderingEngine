

#include "DirectX11Helper.hpp"


namespace Library
{
	namespace DirectX11Helper
	{
		void CreateInputElementDescription(D3D11_INPUT_ELEMENT_DESC* l_descritpion, const char* l_semanticName,
			unsigned int l_semanticIndex, DXGI_FORMAT l_format, unsigned int l_inputSlot,
			unsigned int l_alignedByteOffset, D3D11_INPUT_CLASSIFICATION l_inputSlotClass)
		{
			l_descritpion->SemanticName = l_semanticName;
			l_descritpion->SemanticIndex = l_semanticIndex;
			l_descritpion->Format = l_format;
			l_descritpion->InputSlot = l_inputSlot;
			l_descritpion->AlignedByteOffset = l_alignedByteOffset;
			l_descritpion->InputSlotClass = l_inputSlotClass;
			l_descritpion->InstanceDataStepRate = 0;
		}

		void DisableShaders(ID3D11DeviceContext* l_context, const std::string& l_shader1,
			const std::string& l_shader2, const std::string& l_shader3)
		{
			if ("HS" == l_shader1) {
				l_context->HSSetShader(nullptr, nullptr, 0);
			}
			if ("DS" == l_shader1) {
				l_context->DSSetShader(nullptr, nullptr, 0);
			}
			if ("GS" == l_shader1) {
				l_context->GSSetShader(nullptr, nullptr, 0);
			}

			if ("HS" == l_shader2) {
				l_context->HSSetShader(nullptr, nullptr, 0);
			}
			if ("DS" == l_shader2) {
				l_context->DSSetShader(nullptr, nullptr, 0);
			}
			if ("GS" == l_shader2) {
				l_context->GSSetShader(nullptr, nullptr, 0);
			}

			if ("HS" == l_shader3) {
				l_context->HSSetShader(nullptr, nullptr, 0);
			}
			if ("DS" == l_shader3) {
				l_context->DSSetShader(nullptr, nullptr, 0);
			}
			if ("GS" == l_shader3) {
				l_context->GSSetShader(nullptr, nullptr, 0);
			}

		}

		void CreateRasterizerState(ID3D11Device* l_device, D3D11_FILL_MODE l_fillMode, 
			D3D11_CULL_MODE l_cullMode, bool l_orientation, ID3D11RasterizerState** l_state)
		{
			HRESULT lv_hr{};
			D3D11_RASTERIZER_DESC lv_rsDesc{};
			ZeroMemory(&lv_rsDesc, sizeof(D3D11_RASTERIZER_DESC));

			lv_rsDesc.FillMode = l_fillMode;
			lv_rsDesc.CullMode = l_cullMode;
			lv_rsDesc.FrontCounterClockwise = l_orientation;
			lv_rsDesc.DepthClipEnable = true;
			lv_rsDesc.MultisampleEnable = true;
			lv_rsDesc.ScissorEnable = false;
			lv_rsDesc.AntialiasedLineEnable = false;

			lv_hr = l_device->CreateRasterizerState(&lv_rsDesc, l_state);

			ThrowIfFailed(lv_hr, "CreateRasterizerState() failed.");

		}
	}
}