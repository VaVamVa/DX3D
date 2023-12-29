#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const vector<UINT> indices, const D3D11_USAGE usage = D3D11_USAGE_IMMUTABLE);
	~IndexBuffer();

	void SetIA();

	UINT GetStride() { return stride; }
	UINT GetOffset() { return offset; }
	UINT GetCount() { return count; }

private:
	ID3D11Buffer* buffer = nullptr;

	uint stride;
	uint offset;
	uint count;
};