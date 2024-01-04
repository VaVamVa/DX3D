# 240103

## 1. srv�� �̿��� Texutre ���� Shader�� ������

1. `Sampler State`�� �̿��Ͽ� `Texture`�� `Pixel` ���� �̾� uv ������ �°� Render �Ѵ�.
2. `Sampler State`�� `Texture`�� Ȯ��� ��ҿ��� ���� ���� ������ ����Ѵ�.

3. `ID3D11ShaderResourceView*`�� �������̽� �̿�.
    - `shader->AsSRV("Map")->SetResource(srv);`�� ���̴��� ����

- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)
- [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)

## 2. uv ������ �̿��Ͽ� Texture �׸� ���, Ȯ��, �ڸ���

1. �⺻ ���´� �Ʒ��� ����.

![NDC&UV_coord](/docu_images/NDC_UV_coord.png)

2. �ؽ��Ĵ� ��� ���� "�»��(0, 0) ~ ���ϴ�(1, 1)" ���� �׸��� �ȴ�.

3. `1`�� uv ��(����)�� ���������μ� �ؽ����� ���¸� �ٲ� �� �ִ�.
	1. ���
	2. Ȯ�� (���������� �ڸ��� ����)
	3. �ڸ���


- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)
- [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)


## 3. �� �������� sampler state �̿��ϱ�
uv ������ ���� �� ���� `SamplerState`�� `filter`�� `address`�̿��Ͽ� ó���ϱ�

1. ��� Ȯ��� ���� �� ���� : `Filter`
		- `Point`, `Linear`
2. ������ �������� ���� ���� �κ��� �� ���� : `Address`
    - `Wrap`, `Mirror`, `Clamp`, `Border`

### 1. Filter
scale�� ��ȭ�� ���� pixel ������ �� �κ� �� ����

1. Point
    - ���� : ���� �ѷ���
    - ���� : ���ȿ���� ����� ��

2. Linear
    - ���� : �ε巴�� ó����
    - ���� : ������� �� ����

### 2. Address
`uv value` ������ Texture�� pixel �� ����ִ� �κ��� ó��

1. Clamp (default)
    - ������ ���� "������ pixel�� ��"�� �״�� ä���.

2. Warp
    - "�Ȱ��� ������ �̹���"�� ä���.

3. Mirror
    - "8���� ������ �߽����� ��Ī��Ų �Ȱ��� ������ �̹���"�� ä���.

4. Border
    - �̸� ����� "`BorderColor`"���� ��� ä���.

- [05_TextureSampler.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/05_TextureSampler.fx)
- [Demo/Texture/02_TextureSamplerDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/02_TextureSamplerDemo.cpp)

## 4. Texture load by dialog

1. `Texture` ��ü���� ���ϸ� ���� Texture load �� `srv`�� ���̴��� �ѱ�� ���� ���� ��� ����
    - [Texture.h](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Framework/Renders/Texture.h)

2. `windows.h`�� 'open file by dialog'�� �̿��ϴ� `Path::OpenFileDialog`�� "Texture load" �ϱ�.

```
void TextureLoadDemo::Update()
{
    // ImGui�� Button ������� ������ ����
    if (ImGui::Button("Open Image") == true)
    {
        // ���� ������ �Լ��� ����� �Լ� �����ͷ� ����
        function<void(wstring)> func =
            bind(&TextureLoadDemo::LoadTexture, this, placeholders::_1);

        // HWND handle(������ �ڵ�)�� �ޱ� ���� ����
        GRAPHICS_DESC desc = Graphics::GetDesc();

        /*
        ���� �ҷ����� â ����� �Լ�.
        1. ���ϸ� (�ٷ� �������� �ʱ⿡ �������)
        2. Ȯ���� (�Ʒ��� �̹��� Ȯ������)
        3. �ʱ� ���
        4. â������ file open�����
            � �ൿ�� �������� �����ִ� �Լ� ������
        5. �ҷ����� â �ڵ鷯 ����
        */
        Path::OpenFileDialog(L"", Path::ImageFilter, L"../_Textures/", func, desc.Handle);
    }
}
```

- [Demo/Texture/03_TextureLoadDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/03_TextureLoadDemo.cpp)