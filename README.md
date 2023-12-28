# DX3D

## 1. 231228

#### Framework

framework windows 플랫폼 => `x32(x86)`
- [DX3D_Framework](https://github.com/VaVamVa/DX3D/tree/main/lesson/DirectX11_3D_19)
    - [content_diff](https://github.com/VaVamVa/DX3D/commit/e661cea4d94be84ec221893db3fce17c49edb6ff)

1. Framework 솔루션
    - lib 파일 생성용
2. Game 솔루션
    - 실제 게임 코드 작성용.
- 각 솔루션 속성 잘 알아보기

### 렌더링 파이프라인

IA->VS->RS->PS->OM

#### 1. IA : RAM -> GPU 데이터 보내는 단계
1. 삼각형(폴리곤을 이루는 기본 도형)을 만들어주는 단계
2. 각 Vertices를 배치하여 생성.

#### 2. VS : 실제 Vertices를 2D 세계
1. World 행렬 : 객체 기준의 좌표를 환경 기준의 좌표로 변환.
    - S, R, T 로 구성 : Scale, Rotation, T
2. View 행렬 : 모든 정점의 위치를 카메라 기준으로 변환.
3. Projection 행렬 : 절두체를 그려 원근감을 표현.
    1. 앞의 물체와 뒤의 물체를 직육면체 절두체로 만든 후
    2. 사각뿔 형태의 절두체에 depth 값에 따라 배치.(?)

- Vertex : 정점. 여러가지 정보를 담을 수 있다.

#### Rasterizer State
1. viewport 설정 (window 창)
2. viewport 규모에 맞춰서 pixel 단위로 바꿔줌.

#### Pixel Shader
1. 앞에서 찍은 vertices에 색을 찍는것.
2. 그림자, 안개, 필터, 효과 등 많은

#### Output Merge
1. 출력에 관련한 일.
2. 앞의 모든 과정을 화면에 출력시키는 일
3. swap chain이 여기서 일어남.

#### 추가 용어

1. Shader : GPU에서 이용할 함수.
2. Buffer : CPU에서 data를 담아 GPU로 보내는 역할
3. `ID3D~~~~` vs `D3D~~~~` : interface 형태로 존재하는가.
    - interface 형태로 존재하면, 참조받아서 사용해야 한다.
    - 직접 메모리해제를 해주는게 아닌, `Release` 함수로 해제해야 한다.
    - 



