matrix World;
matrix View;
matrix Projection;

float3 LightDirection = float3(-1, -1, 1);

struct VertexInput
{
    float4 Position : Position;
    float3 Normal : Normal;
};

struct VertexOutput  // NDC 좌표계 기준으로 값 받음.
{
    float4 Position : SV_Position;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Normal = mul(input.Normal, (float3x3)World);  // w 원소 불필요.

    return output;
}


float4 PS(VertexOutput input) : SV_Target
{
    float3 normal = normalize(input.Normal);
    float3 light = -normalize(LightDirection);
    
    float NdotL = saturate(dot(normal, light)) + 0.05f;
    
    return float4(1, 1, 1, 1) * NdotL;
}


RasterizerState FillMode_WireFrame
{
    FillMode = WireFrame;
};

uint Select;
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
}