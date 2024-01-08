matrix World;
matrix View;
matrix Projection;

Texture2D DiffuseMap;

float3 LightDirection = float3(-1, -1, 1);

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

struct VertexOutput  // NDC 좌표계 기준으로 값 받음.
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Uv = input.Uv;
    
    output.Normal = mul(input.Normal, (float3x3)World);  // w 원소 불필요.

    return output;
}

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = normalize(input.Normal);
    /*
    모든 ray tracing 에서 normarlize 해줌.
    만약 light direction을 정규화해서 넘겨주고 있다는 확신이 있다면,
    Shader 보단 CPU에서 정규화 해주는 것이 연산량을 줄일 수 있음.
    */
    float3 light = -normalize(LightDirection);
    
    // saturate : Clamp 같은 역할의 함수
    float NdotL = saturate(dot(normal, light)) + 0.05f;
    
    return DiffuseMap.Sample(LinearSampler, input.Uv) * NdotL;
}

float4 PS_Pure(VertexOutput input) : SV_Target
{
    return DiffuseMap.Sample(LinearSampler, input.Uv);

}


RasterizerState FillMode_WireFrame
{
    FillMode = WireFrame;
};

// Shader 내부에서 효과를 세분화해서 나누기 위해.
// Shader::Draw 함수의 첫번째 인자
technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetRasterizerState(FillMode_WireFrame);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Pure()));
    }
}