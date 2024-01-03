matrix World;
matrix View;
matrix Projection;
float4 Color;

struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput  // NDC ��ǥ�� �������� �� ����.
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

// Shader ���ο��� ȿ���� ����ȭ�ؼ� ������ ����.
// Shader::Draw �Լ��� ù��° ����
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