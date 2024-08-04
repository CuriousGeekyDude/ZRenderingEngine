


cbuffer cbPass : register(b0)
{
    float4x4 gView;
    float4x4 gInvView;
    float4x4 gProj;
    float4x4 gInvProj;
    float4x4 gViewProj;
    float4x4 gInvViewProj;
    float3 gEyePosW;
    float cbPerObjectPad1;
    float2 gRenderTargetSize;
    float2 gInvRenderTargetSize;
    float gNearZ;
    float gFarZ;
    float gTotalTime;
    float gDeltaTime;
    
    float cbPassPad0;
    float cbPassPad1;
    float cbPassPad2;
    float cbPassPad3;
};


struct VertexIn
{
    float3 m_posL : POSITIONL;
};

struct VertexOut
{
    float4 m_posL : POSITIONL;
    float4 m_posW : POSITIONW;
    float4 m_posH : SV_Position;
};

VertexOut VS(VertexIn l_vin)
{
    VertexOut lv_vout;
    
    lv_vout.m_posL = float4(l_vin.m_posL, 1.f);
    lv_vout.m_posW = float4(l_vin.m_posL, 1.f);
    lv_vout.m_posH = mul(float4(l_vin.m_posL, 1.f), gViewProj);
    
    return lv_vout;

}


float4 PS(VertexOut l_vout) : SV_Target
{
    return float4(1.f, 1.f, 1.f, 1.f);
}