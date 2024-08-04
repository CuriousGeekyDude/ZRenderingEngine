#pragma once

#include <DirectXMath.h>

namespace Library
{
	namespace ShaderStructures
	{
		using namespace DirectX;

		struct MainPassConstantBuffer
		{
			XMFLOAT4X4 View;
			XMFLOAT4X4 InvView;
			XMFLOAT4X4 Proj;
			XMFLOAT4X4 InvProj;
			XMFLOAT4X4 ViewProj;
			XMFLOAT4X4 InvViewProj;
			XMFLOAT3 EyePosW;
			float cbPerObjectPad1;
			XMFLOAT2 RenderTargetSize;
			XMFLOAT2 InvRenderTargetSize;
			float NearZ;
			float FarZ;
			float TotalTime;
			float DeltaTime;

			float cbPassPad0;
			float cbPassPad1;
			float cbPassPad2;
			float cbPassPad3;
		};
	}
}