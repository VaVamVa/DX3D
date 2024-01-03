matrix World;
matrix View;
matrix Projection;
float4 Color;

struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput  // NDC 좌표계 기준으로 값 받음.
{
    float4 Position : SV_Position;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    return Color;
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
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}