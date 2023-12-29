#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const vector<UINT> indices, const D3D11_USAGE usage)
{
	D3D11_BUFFER_DESC desc;
	ZeroMem(desc);  // Ȥ�� �𸣴� �ʱ�ȭ

	stride = sizeof(UINT);
	count = indices.size();

	desc.ByteWidth = stride * count;
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
	case D3D11_USAGE_IMMUTABLE:  // CPU�� ���� ��ü�� ����
		break;

	case D3D11_USAGE_DYNAMIC:  // Runtime �߿� CPU���� ������ ����
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;

	case D3D11_USAGE_STAGING:  // 
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}

	D3D11_SUBRESOURCE_DATA sub = { 0 };
	sub.pSysMem = indices.data();

	DEVICE->CreateBuffer(&desc, &sub, &buffer);
}

IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(buffer);
}

void IndexBuffer::SetIA()
{
	DEVICE_CONTEXT->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
}
