#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::~VertexBuffer()
{
	SAFE_RELEASE(buffer);
}

void VertexBuffer::SetIA()
{
	// buffer의 내용을 IA(GPU)로 전달
	DEVICE_CONTEXT->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
}
