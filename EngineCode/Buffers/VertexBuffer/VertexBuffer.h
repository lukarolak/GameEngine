#pragma once
#include <vector>
#include <Vertex/Vertex.h>
#include <Buffers/Buffer.h>
#include <Buffers/VertexBuffer/CreateVertexBufferParams.h>
class CVertexBuffer : public CBuffer
{
public:
	void CreateVertexBuffer(const CCreateVertexBufferParams& Params);
	void Release(const VkDevice& Device);
private:
};