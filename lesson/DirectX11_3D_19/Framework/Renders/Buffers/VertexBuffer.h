#pragma once

class VertexBuffer
{
public:
	template<typename T>
	VertexBuffer(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);
	~VertexBuffer();

	ID3D11Buffer* GetBuffer() { return buffer; }

	uint GetStride() { return stride; }
	uint GetOffset() { return offset; }
	uint GetCount() { return count; }

	void SetIA();

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride = 0;
	uint offset = 0;  
	uint count = 0;
};

template<typename T>
inline VertexBuffer::VertexBuffer(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);  // Vertex buffer의 크기
	count = vertices.size();  // Vertex buffers의 개수
	// offset : stirde * count(한 메모리 구역) 내에서 특정 속성만 읽고 싶을때.

	D3D11_BUFFER_DESC desc;  // 견적서
	ZeroMem(desc);

	desc.Usage = usage;  // cpu에서 사용할 수 있는지
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // 사용할 목적
	desc.ByteWidth = stride * count;  // 총 메모리 크기. VRAM에서 확보할 공간

	switch (usage)
	{
		case D3D11_USAGE_DEFAULT:
		case D3D11_USAGE_IMMUTABLE:  // CPU에 접근 자체를 막음
			break;

		case D3D11_USAGE_DYNAMIC:  // Runtime 중에 CPU에서 데이터 조작
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case D3D11_USAGE_STAGING:  // 
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
	}

	D3D11_SUBRESOURCE_DATA sub = { 0 };	// 안에 포인터 변수가 있으면 ZeroMemory (쓰레기값 방지)
	sub.pSysMem = vertices.data();		// 실제로 그릴 데이터의 시작 주소

	HRESULT hr = DEVICE->CreateBuffer(&desc, &sub, &buffer);
	Check(hr);
}
