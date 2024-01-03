matrix World;
matrix View;
matrix Projection;
Texture2D Map;

struct VertexInput
{
    float4 Position : Position;
    float2 Uv : Uv;
};

struct VertexOutput  // NDC 좌표계 기준으로 값 받음.
{
    float4 Position : SV_Position;
    float2 Uv : Uv;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Uv = input.Uv;

    return output;
}

// 1. pixel의 값을 뽑아서 축소 혹은 확대를 해주는 것.
// 2. 확대와 축소에서 오는 색깔 보간
SamplerState Samp;
float4 PS(VertexOutput input) : SV_Target
{
    /*
    if (input.Uv.x < 0.5f)  // 가로(임의) 비율에 따라 다른 색 반환
        return float4(1, 0, 0, 1);
    */
    
    return Map.Sample(Samp, input.Uv);
}

// 3. filter 효과 먹이기
uint Filter;

SamplerState Sampler_Filter_Point
{
    Filter = MIN_MAG_MIP_POINT;  // 계단효과 처리, 색이 뚜렷함.
};

SamplerState Sampler_Filter_Linear
{
    Filter = MIN_MAG_MIP_LINEAR;  // 부드럽게 처리, 흐리멍텅함.
};

float4 PS_Filter(VertexOutput input) : SV_Target
{
    if (Filter == 0)
        return Map.Sample(Sampler_Filter_Point, input.Uv);
    
    if (Filter == 1)
        return Map.Sample(Sampler_Filter_Linear, input.Uv);
    
    return Map.Sample(Samp, input.Uv);

}

// 4. 비어있는 부분에 어떻게 보간할지 결정하기.
uint Address;

// 똑같은 이미지를 찍어내어 보간한다.
SamplerState Sampler_Address_Wrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

// 상하좌우 순서를 따라서 거울상으로 찍어내어 보간한다.
SamplerState Sampler_Address_Mirror
{
    AddressU = Mirror;
    AddressV = Mirror;

    BorderColor = float4(0, 1, 1, 1);
};

// 정해진 구역만 표현하고 마지막 Pixel 색으로 보간한다. (default)
SamplerState Sampler_Address_Clamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};

// 설정한 border color로 보간한다.
SamplerState Sampler_Address_Border
{
    AddressU = Border;
    AddressV = Border;

    BorderColor = float4(0, 1, 1, 1);
};

float4 PS_Address(VertexOutput input) : SV_Target
{
    if (Address == 0)
        return Map.Sample(Sampler_Address_Wrap, input.Uv);
    
    if (Address == 1)
        return Map.Sample(Sampler_Address_Mirror, input.Uv);
    
    if (Address == 2)
        return Map.Sample(Sampler_Address_Clamp, input.Uv);
    
    if (Address == 3)
        return Map.Sample(Sampler_Address_Border, input.Uv);
    
    return Map.Sample(Samp, input.Uv);

}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Filter()));
    }

    pass P2
    {

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Address()));
    }
}