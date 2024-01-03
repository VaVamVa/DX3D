# 240103

## Texture 불러오기

1. `Sampler State`를 이용하여 `Texture`의 `Pixel` 값을 뽑아 uv 비율에 맞게 Render 한다.
2. `Sampler State`는 `Texture`의 확대와 축소에서 오는 색의 보간을 담당한다.
	1. 축소 확대로 인한 색 보간 : `Filter`
		- `Point`, `Linear`
	2. 비율의 변경으로 인해 남는 부분의 색 보간 : `Address`
		- `Wrap`, `Mirror`, `Clamp`, `Border`

- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)

## Texture uv

1. 기본 형태는 아래와 같다.
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

2. 텍스쳐는 어떠한 경우는 "좌상단(0, 0) ~ 우하단(1, 1)" 으로 그리게 된다.

3. `1`의 uv 값을 변경함으로서 텍스쳐의 형태를 바꿀 수 있다.
	1. 축소
	2. 확대
	3. 자르기

4. `3-1`과 `3-2`를 보완할 


- [04_Texture.fx](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/_Shaders/04_Texture.fx)
- [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)
- [Demo/Texture/01_TextureSamplerDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/02_TextureSamplerDemo.cpp)

## Texture Load 객체화