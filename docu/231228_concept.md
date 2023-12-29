231228
<hr/>


### Framework

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
Input Assembler
1. 삼각형(폴리곤을 이루는 기본 도형)을 만들어주는 단계
2. 각 Vertices를 배치하여 생성.

#### 2. VS : 실제 Vertices를 2D 세계(화면)에 맞춤
Vertex Shader
1. World 행렬 : 객체 기준의 좌표를 환경 기준의 좌표로 변환.
    - S, R, T 로 구성 : Scale, Rotation, Translation
    - 초기에 `Vertex Buffer`에 담긴 data는 자기 자신(객체)에 대한 정보들이고,<br>이를 환경 기준으로 바꿔줌
2. View 행렬 : 모든 정점의 위치를 카메라 기준으로 변환.
3. Projection 행렬 : 절두체를 그려 원근감을 표현.
    1. 앞의 물체와 뒤의 물체를 직육면체 절두체로 만든 후
    2. 사각뿔 형태의 절두체에 depth 값에 따라 배치.(?)

- Vertex : 정점. 여러가지 정보를 담을 수 있다.
    - 위치, depth-stancil value, 기타 효과 등등 

#### 3. RS : 뷰포트로 변환
Raterization State
1. viewport 설정 (window 창)
2. viewport 규모에 맞춰서 pixel 단위로 바꿔줌.

#### 4. PS : 주어진 특성들 총합해 pixel 생상 계산
Pixel Shader
1. 앞에서 주어진 vertices에 색을 넣는 것.
2. 빛 반사, 그림자, 안개, 필터, 효과 등 많은 값들을 통합하여 계산함.

#### 5. OM : 픽셀 단편을 후면 버퍼에 기록
Output Merge
1. 출력에 관련한 일.
2. 앞의 모든 과정의 결과물을 화면에 출력시키는 일
3. swap chain이 여기서 일어남.

#### (+) 추가 용어

1. `Shader` : GPU에서 이용할 함수.
    - (+) CS : `Compute Shader`,<br>GPU의 코어가 많은 점을 이용하여<br>연산량이 많은 연산들을 GPU에서 처리하게끔 하는 Shader
2. `Buffer` : CPU에서 data를 담아 GPU로 보내는 역할
    - `Shader`에서 이용할 Buffer는 Shader와 메모리 사용 정도를 맞춰야 한다(?)
3. `ID3D~~~~` vs `D3D~~~~` : interface 형태로 존재하는가.
    - 참조받아서 사용해야 한다.
    - 직접 메모리해제를 해주는게 아닌, `Release` 함수로 해제해야 한다.
    - `DESC` 객체를 통해 상세 data를 전달해야 한다.
