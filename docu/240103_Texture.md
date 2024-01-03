# 240103

## Texture �ҷ�����

1. `Sampler State`�� �̿��Ͽ� `Texture`�� `Pixel` ���� �̾� uv ������ �°� Render �Ѵ�.
2. `Sampler State`�� `Texture`�� Ȯ��� ��ҿ��� ���� ���� ������ ����Ѵ�.
	1. ��� Ȯ��� ���� �� ���� : `Filter`
		- `Point`, `Linear`
	2. ������ �������� ���� ���� �κ��� �� ���� : `Address`
		- `Wrap`, `Mirror`, `Clamp`, `Border`

- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)

## Texture uv

1. �⺻ ���´� �Ʒ��� ����.
```
(u, v)
0,0		1,0
 -------
|		|
|		|
|		|
 -------
0,1		1,1
```

2. �ؽ��Ĵ� ��� ���� "�»��(0, 0) ~ ���ϴ�(1, 1)" ���� �׸��� �ȴ�.

3. `1`�� uv ���� ���������μ� �ؽ����� ���¸� �ٲ� �� �ִ�.
	1. ���
	2. Ȯ��
	3. �ڸ���

4. `3-1`�� `3-2`�� ������ 


- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)
- [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)
- [Demo/Texture/01_TextureSamplerDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/02_TextureSamplerDemo.cpp)

## Texture Load ��üȭ