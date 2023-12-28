#pragma once

class VertexBuffer
{
public:
	~VertexBuffer();

	template<typename T>
	void Create(const vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT);

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
inline void VertexBuffer::Create(const vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);
	count = vertices.size();

	D3D11_BUFFER_DESC desc;
	ZeroMem(desc);

	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = stride * count;

	switch (usage)
	{
		case D3D11_USAGE_DEFAULT:
		case D3D11_USAGE_IMMUTABLE:
			break;

		case D3D11_USAGE_DYNAMIC:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			break;

		case D3D11_USAGE_STAGING:
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
			break;
	}

	D3D11_SUBRESOURCE_DATA sub = { 0 };	// 안에 포인터 변수가 있으면 ZeroMemory
	sub.pSysMem = vertices.data();		// 실제로 그릴 데이터의 시작 주소

	HRESULT hr = DEVICE->CreateBuffer(&desc, &sub, &buffer);
	Check(hr);
}
