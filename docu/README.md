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


## 4. 240104

#### [240104_Cube](docu/240103_Cube.md)
1. 
2. 

#### [240104_Mesh](docu/240104_Mesh.md)
2. 램버트 기법.

- [content_diff]()