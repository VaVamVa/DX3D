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
    output.Position = input.Position;

    return output;
}

float4 PS1(VertexOutput input) : SV_Target
{
    return float4(1, 0, 0, 1);
}

float4 PS2(VertexOutput input) : SV_Target
{
    return float4(0, 1, 0, 1);
}

float4 PS3(VertexOutput input) : SV_Target
{
    return float4(0, 0, 1, 1);
}

// Shader 내부에서 효과를 세분화해서 나누기 위해.
// Shader::Draw 함수의 첫번째 인자
technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS1()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS2()));
    }
}

technique11 T1
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS3()));
    }
}