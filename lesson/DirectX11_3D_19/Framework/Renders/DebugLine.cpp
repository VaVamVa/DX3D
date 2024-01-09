#include "Framework.h"
#include "DebugLine.h"

DebugLine::DebugLine()
{
	shader = new Shader(L"09_DebugLine.fx");

	vertices.assign(MAX_DEBUG_LINE, VertexColor());
	
	vb = new VertexBuffer(vertices);
}

DebugLine::~DebugLine()
{
	SAFE_DELETE(vb);
	SAFE_DELETE(shader);
}

void DebugLine::RenderLine(Vector3 start, Vector3 end)
{
	RenderLine(start, end, Color(0, 1, 0, 1));
}

void DebugLine::RenderLine(Vector3 start, Vector3 end, float r, float g, float b)
{
	RenderLine(start, end, Color(r, g, b, 1));
}

void DebugLine::RenderLine(Vector3 start, Vector3 end, Color color)
{
	vertices[drawCount].Color = color;
	vertices[drawCount++].Position = start;

	vertices[drawCount].Color = color;
	vertices[drawCount++].Position = end;
}

void DebugLine::RenderLine(float x, float y, float z, float x2, float y2, float z2)
{
	RenderLine(Vector3(x, y, z), Vector3(x2, y2, z2), Color(0, 1, 0, 1));
}

void DebugLine::RenderLine(float x, float y, float z, float x2, float y2, float z2, float r, float g, float b)
{
	RenderLine(Vector3(x, y, z), Vector3(x2, y2, z2), Color(r, g, b, 1));
}

void DebugLine::RenderLine(float x, float y, float z, float x2, float y2, float z2, Color color)
{
	RenderLine(Vector3(x, y, z), Vector3(x2, y2, z2), color);
}

void DebugLine::Update()
{
	Matrix world;
	D3DXMatrixIdentity(&world);

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->GetProjectionMatrix());
}

void DebugLine::Render()
{
	if (drawCount < 1) return;

	DEVICE_CONTEXT->UpdateSubresource(vb->GetBuffer(), 0, NULL, vertices.data(), sizeof(VertexColor) * drawCount, 0);

	vb->SetIA();
	DEVICE_CONTEXT->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(0, 0, drawCount);

	drawCount = 0;
	vertices.assign(MAX_DEBUG_LINE, VertexColor());
}
