#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	// buffer�� ������ IA(GPU)�� ����
	DEVICE_CONTEXT->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
