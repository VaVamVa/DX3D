# 240103

## 1. srv를 이용해 Texutre 정보 Shader로 보내기

1. `Sampler State`를 이용하여 `Texture`의 `Pixel` 값을 뽑아 uv 비율에 맞게 Render 한다.
2. `Sampler State`는 `Texture`의 확대와 축소에서 오는 색의 보간을 담당한다.

3. `ID3D11ShaderResourceView*`로 인터페이스 이용.
    - `shader->AsSRV("Map")->SetResource(srv);`로 쉐이더에 전달

- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)
- [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)

## 2. uv 비율을 이용하여 Texture 그림 축소, 확대, 자르기

1. 기본 형태는 아래와 같다.

![NDC&UV_coord](/docu_images/NDC_UV_coord.png)

2. 텍스쳐는 어떠한 경우는 "좌상단(0, 0) ~ 우하단(1, 1)" 으로 그리게 된다.

3. `1`의 uv 값(비율)을 변경함으로서 텍스쳐의 형태를 바꿀 수 있다.
	1. 축소
	2. 확대 (무조건적인 자르기 수반)
	3. 자르기


- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)
- [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)


## 3. 색 보간으로 sampler state 이용하기
uv 비율에 대한 색 보간 `SamplerState`의 `filter`와 `address`이용하여 처리하기

1. 축소 확대로 인한 색 보간 : `Filter`
		- `Point`, `Linear`
2. 비율의 변경으로 인해 남는 부분의 색 보간 : `Address`
    - `Wrap`, `Mirror`, `Clamp`, `Border`

### 1. Filter
scale의 변화로 오는 pixel 사이의 빈 부분 색 보간

1. Point
    - 장점 : 색이 뚜렷함
    - 단점 : 계단효과가 생기게 됨

2. Linear
    - 장점 : 부드럽게 처리됨
    - 단점 : 흐려보일 수 있음

### 2. Address
`uv value` 내에서 Texture의 pixel 중 비어있는 부분의 처리

1. Clamp (default)
    - 구역에 따라 "마지막 pixel의 색"을 그대로 채운다.

2. Warp
    - "똑같은 비율의 이미지"로 채운다.

3. Mirror
    - "8방의 기준을 중심으로 대칭시킨 똑같은 비율의 이미지"로 채운다.

4. Border
    - 미리 약속한 "`BorderColor`"으로 모두 채운다.

- [05_TextureSampler.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/05_TextureSampler.fx)
- [Demo/Texture/02_TextureSamplerDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/02_TextureSamplerDemo.cpp)

## 4. Texture load by dialog

1. `Texture` 객체에서 파일명에 따른 Texture load 와 `srv`로 쉐이더에 넘기기 등의 동작 모두 수행
    - [Texture.h](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Framework/Renders/Texture.h)

2. `windows.h`의 'open file by dialog'를 이용하는 `Path::OpenFileDialog`로 "Texture load" 하기.

```
void TextureLoadDemo::Update()
{
    // ImGui의 Button 기능으로 수행할 동작
    if (ImGui::Button("Open Image") == true)
    {
        // 실제 실행할 함수를 만들어 함수 포인터로 생성
        function<void(wstring)> func =
            bind(&TextureLoadDemo::LoadTexture, this, placeholders::_1);

        // HWND handle(윈도우 핸들)을 받기 위한 수단
        GRAPHICS_DESC desc = Graphics::GetDesc();

        /*
        파일 불러오기 창 만드는 함수.
        1. 파일명 (바로 실행하지 않기에 비어있음)
        2. 확장자 (아래는 이미지 확장자임)
        3. 초기 경로
        4. 창에서의 file open결과로
            어떤 행동을 수행할지 정해주는 함수 포인터
        5. 불러오기 창 핸들러 제시
        */
        Path::OpenFileDialog(L"", Path::ImageFilter, L"../_Textures/", func, desc.Handle);
    }
}
```

- [Demo/Texture/03_TextureLoadDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/03_TextureLoadDemo.cpp)