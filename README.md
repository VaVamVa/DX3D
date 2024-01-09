# DX3D

<br>

## 1. 231228

#### [231228_concept](docu/231228_concept.md)

1. rendring pipeline 간단한 개념 정리
2. 기타 용어들 간단 정리
3. Vertecies 찍어보기 중. (content_diff 참고)
<br>

- [content_diff](https://github.com/VaVamVa/DX3D/commit/666f360970b153f77bf4441d536cf9d3c5185b2b)


<br>

## 2. 231229

#### [231229_Draw](docu/231229_Draw.md)

1. 선과 면 그리기
2. NDC 좌표계와 World 좌표계
3. Index Buffer를 이용한 Vertex 수 줄이기
    - 최적화
<br>

- [content_diff](https://github.com/VaVamVa/DX3D/commit/8c6f7a9fcd728711caabed01476bcf2a4c3256d5)

<br>


## 3. 240102

#### [240102_Draw2](docu/240102_Draw2.md)

1. grid 그리기
2. Camera 생성
<br>

- [content_diff](https://github.com/VaVamVa/DX3D/commit/c8b696304621a38546c341fd181ea44befd43bbe)

<br>


## 4. 240103

#### [240103_Texture](docu/240103_Texture.md)
1. srv를 이용해 Texutre 정보 Shader로 보내기
2. uv 비율을 이용하여 Texture 그림 축소, 확대, 자르기
3. uv 비율에 대한 색 보간 `SamplerState`의 `filter`와 `address`이용하여 처리하기
4. `windows.h`의 'open file by dialog'를 이용하는 `Path::OpenFileDialog`를 이용한 "Texture load"

#### [240103_Cube](docu/240103_Cube.md)
1. 정육면체 cube 그리기
<br>

- [content_diff](https://github.com/VaVamVa/DX3D/commit/3b9c800bc0d5f6a543ede0bd12986cc621ccc478)

### 과제
1. 그림 4개로 잘라서 완전한 그림 만들기
    - [Demo/Texture/01_TextureDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Texture/01_TextureDemo.cpp)
2. Cube 상하 전후 좌우 움직이게 하기 (world buffer 이용)
    - [Demo/Mesh/01_CubeDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Mesh/01_CubeDemo.cpp)
<br>

- [content_diff](https://github.com/VaVamVa/DX3D/commit/a68ead6679e67be69ec26eac6e3821416140dd83)

<br>


## 5. 240104

#### [240104_Cube](docu/240103_Cube.md)
1. `240103` 과제의 cube는 world 좌표계의 중심으로 cube를 움직임.
2. `1`의 상황을 해결하기 위해, 각 객체의 축 방향좌표를 이용한 이동 구현

#### [240104_Mesh](docu/240104_Mesh.md)
1. 실제 빛이 주는 효과들을 렌더할 수 있는 객체의 super class 생성
2. 또한 이 class는 각 방향벡터 및 SRT 벡터를 가짐.
3. 이전과 다르게 필요할 때에만 버퍼에 담아 쉐이더로 전달하도록 변경.
4. 램버트 기법을 이용한 Texture의 고유색상과 빛과의 관계 연산 (Diffuse)

- [content_diff](https://github.com/VaVamVa/DX3D/commit/6075e291e7e3db08d961917d9e26a09bf37225e6)

<br>


## 6. 240105

#### [240105_Meshes](docu/240105_Meshes.md)
도형들 그리기
1. Quad : 2차원 사각형
2. Cube : 3차원 육면체
3. Grid : 2차원 타일 (정사각형의 정사각 그룹)
4. Sphere : 3차원 구

- [content_diff](https://github.com/VaVamVa/DX3D/commit/e0ebfbe555cd90ba47ec0732e59987c94b36e509)

### 과제
1. 지구를 `cube`기준으로 공전시키기
2. 지구를 23.5도 기울려서 자전시키고 공전시키기
    - [02_MeshDemo.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Mesh/02_MeshDemo.cpp)
3. 태양계 만들기
    - [02_SolarSystemHW.cpp](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/HW/Mesh/02_SolarSystemHW.cpp)

- [content_diff](https://github.com/VaVamVa/DX3D/commit/3b6a201ad3327af1178dfb08936a8c5a2ddfafe6)

<br>


## 7. 240108

#### [240105_HW_SolarSystem](https://github.com/VaVamVa/DX3D/blob/main/lesson/DirectX11_3D_19/Game/Demo/Task/SolarSystem.h)

`240105` 태양계 그리기 과제 같이 풀어보기

#### [240108_Meshes](docu/240105_Meshes.md)

1. Cylinder : 3차원 원기둥 

- [content_diff](https://github.com/VaVamVa/DX3D/commit/0ca95eebd569bc3975076056b49a110fa0d56d52)

<br>


## 8. 240109

#### [240109_HeightMap](docu/240109_HeightMap.md)

1. tile map 그리기
2. tile map의 특정위치의 높이 값 받아오기
3. 특정위치 높이 값에 대한 DebugLine 만들기 (구현파일 그대로 받아옴)

- [content_diff](https://github.com/VaVamVa/DX3D/commit/90c84a9b2a1e2f51aa9d7b9a231c2b108c903e52)
