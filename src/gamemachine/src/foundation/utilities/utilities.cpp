﻿#include "stdafx.h"
#include "utilities.h"
#include "foundation/gamemachine.h"
#include "gmengine/gmgameworld.h"

const GMVec3& GMPrimitiveCreator::one3()
{
	static GMVec3 o (1, 1, 1);
	return o;
}

const GMVec2& GMPrimitiveCreator::one2()
{
	static GMVec2 o(1, 1);
	return o;
}

GMfloat* GMPrimitiveCreator::origin()
{
	static GMfloat o[3] = { 0 };
	return o;
}

void GMPrimitiveCreator::createCube(const GMVec3& halfExtents, OUT GMModel** out)
{
	static const GMVec3 s_vertices[8] = {
		GMVec3(-1, -1, -1),
		GMVec3(-1, 1, -1),
		GMVec3(1, -1, -1),
		GMVec3(1, 1, -1),

		GMVec3(-1, -1, 1),
		GMVec3(-1, 1, 1),
		GMVec3(1, -1, 1),
		GMVec3(1, 1, 1),
	};

	GMVec3 vertices_vec[8];
	GMFloat4 vertices[8];
	for (GMint i = 0; i < GM_array_size(vertices); ++i)
	{
		vertices_vec[i] = s_vertices[i] * halfExtents;
		vertices_vec[i].loadFloat4(vertices[i]);
	}

	/*
	采用
	1 3
	0 2
	顶点顺序来绘制每一个面
	*/

	GMModel* model = new GMModel();
	model->setPrimitiveTopologyMode(GMTopologyMode::Triangles);
	model->setType(GMModelType::Model3D);
	GMMesh* face = new GMMesh(model);

	//Front
	{
		GMVertex V0 = {
			{ vertices[0][0], vertices[0][1], vertices[0][2] }, //position
			{ 0, 0, -1.f }, //normal
			{ 0, 1 }, //texcoord
		},
		V1 = {
			{ vertices[1][0], vertices[1][1], vertices[1][2] }, //position
			{ 0, 0, -1.f }, //normal
			{ 0, 0 }, //texcoord
		},
		V2 = {
			{ vertices[2][0], vertices[2][1], vertices[2][2] }, //position
			{ 0, 0, -1.f }, //normal
			{ 1, 1 }, //texcoord
		},
		V3 = {
			{ vertices[3][0], vertices[3][1], vertices[3][2] }, //position
			{ 0, 0, -1.f }, //normal
			{ 1, 0 }, //texcoord
		};
		face->vertex(V0);
		face->vertex(V1);
		face->vertex(V2);
		face->vertex(V1);
		face->vertex(V3);
		face->vertex(V2);
	}

	//Back
	{
		GMVertex V0 = {
			{ vertices[6][0], vertices[6][1], vertices[6][2] }, //position
			{ 0, 0, 1.f }, //normal
			{ 0, 1 }, //texcoord
		},
		V1 = {
			{ vertices[7][0], vertices[7][1], vertices[7][2] }, //position
			{ 0, 0, 1.f }, //normal
			{ 0, 0 }, //texcoord
		},
		V2 = {
			{ vertices[4][0], vertices[4][1], vertices[4][2] }, //position
			{ 0, 0, 1.f }, //normal
			{ 1, 1 }, //texcoord
		},
		V3 = {
			{ vertices[5][0], vertices[5][1], vertices[5][2] }, //position
			{ 0, 0, 1.f }, //normal
			{ 1, 0 }, //texcoord
		};
		face->vertex(V0);
		face->vertex(V1);
		face->vertex(V2);
		face->vertex(V1);
		face->vertex(V3);
		face->vertex(V2);
	}

	//Left
	{
		GMVertex V0 = {
			{ vertices[4][0], vertices[4][1], vertices[4][2] }, //position
			{ -1.f, 0, 0 }, //normal
			{ 0, 1 }, //texcoord
		},
		V1 = {
			{ vertices[5][0], vertices[5][1], vertices[5][2] }, //position
			{ -1.f, 0, 0 }, //normal
			{ 0, 0 }, //texcoord
		},
		V2 = {
			{ vertices[0][0], vertices[0][1], vertices[0][2] }, //position
			{ -1.f, 0, 0 }, //normal
			{ 1, 1 }, //texcoord
		},
		V3 = {
			{ vertices[1][0], vertices[1][1], vertices[1][2] }, //position
			{ -1.f, 0, 0 }, //normal
			{ 1, 0 }, //texcoord
		};
		face->vertex(V0);
		face->vertex(V1);
		face->vertex(V2);
		face->vertex(V1);
		face->vertex(V3);
		face->vertex(V2);
	}

	//Right
	{
		GMVertex V0 = {
			{ vertices[2][0], vertices[2][1], vertices[2][2] }, //position
			{ 1.f, 0, 0 }, //normal
			{ 0, 1 }, //texcoord
		},
		V1 = {
			{ vertices[3][0], vertices[3][1], vertices[3][2] }, //position
			{ 1.f, 0, 0 }, //normal
			{ 0, 0 }, //texcoord
		},
		V2 = {
			{ vertices[6][0], vertices[6][1], vertices[6][2] }, //position
			{ 1.f, 0, 0 }, //normal
			{ 1, 1 }, //texcoord
		},
		V3 = {
			{ vertices[7][0], vertices[7][1], vertices[7][2] }, //position
			{ 1.f, 0, 0 }, //normal
			{ 1, 0 }, //texcoord
		};
		face->vertex(V0);
		face->vertex(V1);
		face->vertex(V2);
		face->vertex(V1);
		face->vertex(V3);
		face->vertex(V2);
	}

	//Bottom
	{
		GMVertex V0 = {
			{ vertices[4][0], vertices[4][1], vertices[4][2] }, //position
			{ 0, -1.f, 0 }, //normal
			{ 0, 1 }, //texcoord
		},
		V1 = {
			{ vertices[0][0], vertices[0][1], vertices[0][2] }, //position
			{ 0, -1.f, 0 }, //normal
			{ 0, 0 }, //texcoord
		},
		V2 = {
			{ vertices[6][0], vertices[6][1], vertices[6][2] }, //position
			{ 0, -1.f, 0 }, //normal
			{ 1, 1 }, //texcoord
		},
		V3 = {
			{ vertices[2][0], vertices[2][1], vertices[2][2] }, //position
			{ 0, -1.f, 0 }, //normal
			{ 1, 0 }, //texcoord
		};
		face->vertex(V0);
		face->vertex(V1);
		face->vertex(V2);
		face->vertex(V1);
		face->vertex(V3);
		face->vertex(V2);
	}

	//Top
	{
		GMVertex V0 = {
			{ vertices[1][0], vertices[1][1], vertices[1][2] }, //position
			{ 0, 1.f, 0 }, //normal
			{ 0, 1 }, //texcoord
		},
		V1 = {
			{ vertices[5][0], vertices[5][1], vertices[5][2] }, //position
			{ 0, 1.f, 0 }, //normal
			{ 0, 0 }, //texcoord
		},
		V2 = {
			{ vertices[3][0], vertices[3][1], vertices[3][2] }, //position
			{ 0, 1.f, 0 }, //normal
			{ 1, 1 }, //texcoord
		},
		V3 = {
			{ vertices[7][0], vertices[7][1], vertices[7][2] }, //position
			{ 0, 1.f, 0 }, //normal
			{ 1, 0 }, //texcoord
		};
		face->vertex(V0);
		face->vertex(V1);
		face->vertex(V2);
		face->vertex(V1);
		face->vertex(V3);
		face->vertex(V2);
	}

	*out = model;
}

void GMPrimitiveCreator::createQuadrangle(const GMVec2& halfExtents, GMfloat z, OUT GMModel** out)
{
	constexpr GMfloat texcoord[4][2] =
	{
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 1 },
		{ 1, 0 },
	};

	// 排列方式：
	// 2 4
	// 1 3
	const GMfloat x = halfExtents.getX(), y = halfExtents.getY();
	const GMfloat s_vertices[4][3] = {
		{ -x, -y, z },
		{ -x, y, z },
		{ x, -y, z },
		{ x, y, z },
	};

	GMModel* model = new GMModel();
	model->setPrimitiveTopologyMode(GMTopologyMode::TriangleStrip);
	GMMesh* mesh = new GMMesh(model);

	GMVertex V1 = {
		{ s_vertices[0][0], s_vertices[0][1], s_vertices[0][2] }, //position
		{ 0, -1.f, 0 }, //normal
		{ texcoord[0][0], texcoord[0][1] }, //texcoord
	},
	V2 = {
		{ s_vertices[1][0], s_vertices[1][1], s_vertices[1][2] }, //position
		{ 0, -1.f, 0 }, //normal
		{ texcoord[1][0], texcoord[1][1] }, //texcoord
	},
	V3 = {
		{ s_vertices[2][0], s_vertices[2][1], s_vertices[2][2] }, //position
		{ 0, -1.f, 0 }, //normal
		{ texcoord[2][0], texcoord[2][1] }, //texcoord
	},
	V4 = {
		{ s_vertices[3][0], s_vertices[3][1], s_vertices[3][2] }, //position
		{ 0, -1.f, 0 }, //normal
		{ texcoord[3][0], texcoord[3][1] }, //texcoord
	};
	mesh->vertex(V1);
	mesh->vertex(V2);
	mesh->vertex(V3);
	mesh->vertex(V4);

	*out = model;
}

void GMPrimitiveCreator::createQuad(GMfloat extents[3], GMfloat position[3], OUT GMModel** obj, IPrimitiveCreatorShaderCallback* shaderCallback, GMModelType type, GMCreateAnchor anchor, GMfloat (*customUV)[12])
{
	static constexpr GMfloat v_anchor_center[] = {
		-1, 1, 0,
		-1, -1, 0,
		1, -1, 0,
		1, 1, 0,
	};

	const GMfloat(*_customUV)[12] = customUV ? customUV : &v_anchor_center;
	const GMfloat(&uvArr)[12] = *_customUV;

	static constexpr GMfloat v_anchor_top_left[] = {
		0, 0, 0,
		0, -2, 0,
		2, -2, 0,
		2, 0, 0,
	};

	const GMfloat(&v)[12] = (anchor == TopLeft) ? v_anchor_top_left : v_anchor_center;

	static constexpr GMint indices[] = {
		0, 3, 1,
		2, 1, 3,
	};

	GMModel* model = new GMModel();

	// 实体
	GMfloat t[12];
	for (GMint i = 0; i < 12; ++i)
	{
		t[i] = extents[i % 3] * v[i] + position[i % 3];
	}

	{
		model->setType(type);
		model->setPrimitiveTopologyMode(GMTopologyMode::TriangleStrip);

		GMMesh* body = new GMMesh(model);
		GMFloat4 f4_vertex, f4_normal, f4_uv;
		for (GMint i = 0; i < 2; ++i)
		{
			for (GMint j = 0; j < 3; ++j) // j表示面的一个顶点
			{
				GMint idx = i * 3 + j; //顶点的开始
				GMint idx_next = i * 3 + (j + 1) % 3;
				GMint idx_prev = i * 3 + (j + 2) % 3;
				GMVec2 uv(uvArr[indices[idx] * 3], uvArr[indices[idx] * 3 + 1]);
				GMVec3 vertex(t[indices[idx] * 3], t[indices[idx] * 3 + 1], t[indices[idx] * 3 + 2]);
				GMVec3 vertex_prev(t[indices[idx_prev] * 3], t[indices[idx_prev] * 3 + 1], t[indices[idx_prev] * 3 + 2]),
					vertex_next(t[indices[idx_next] * 3], t[indices[idx_next] * 3 + 1], t[indices[idx_next] * 3 + 2]);
				GMVec3 normal = Cross(vertex - vertex_prev, vertex_next - vertex);
				normal = FastNormalize(normal);

				vertex.loadFloat4(f4_vertex);
				normal.loadFloat4(f4_normal);
				uv.loadFloat4(f4_uv);

				GMVertex v = {
					{ f4_vertex[0], f4_vertex[1], f4_vertex[2] },
					{ f4_normal[0], f4_normal[1], f4_normal[2] },
				};

				if (customUV)
				{
					v.texcoords[0] = f4_uv[0];
					v.texcoords[1] = 1 - f4_uv[1];
				}
				else
				{
					v.texcoords[0] = (f4_uv[0] + 1) / 2;
					v.texcoords[1] = 1 - (f4_uv[1] + 1) / 2;
				}

				v.color[0] = v.color[1] = v.color[2] = 1.f;
				body->vertex(v);
			}
		}
		if (shaderCallback)
			shaderCallback->onCreateShader(model->getShader());
	}

	*obj = model;
}

void GMPrimitiveCreator::createQuad3D(GMfloat extents[3], GMfloat position[12], OUT GMModel** obj, IPrimitiveCreatorShaderCallback* shaderCallback, GMModelType type, GMfloat(*customUV)[8])
{
	static constexpr GMfloat defaultUV[] = {
		-1, 1,
		-1, -1,
		1, -1,
		1, 1,
	};

	const GMfloat(*_pos)[12] = (GMfloat(*)[12])(position);
	const GMfloat(*_uv)[8] = customUV ? customUV : (GMfloat(*)[8])defaultUV;
	const GMfloat(&uvArr)[8] = *_uv;
	const GMfloat(&v)[12] = *_pos;

	static constexpr GMint indices[] = {
		0, 3, 1,
		2, 1, 3,
	};

	GMModel* model = new GMModel();

	// 实体
	GMfloat t[12];
	for (GMint i = 0; i < 12; i++)
	{
		t[i] = extents[i % 3] * v[i];
	}

	{
		model->setType(type);
		GMMesh* body = new GMMesh(model);
		model->setPrimitiveTopologyMode(GMTopologyMode::TriangleStrip);

		GMFloat4 f4_vertex, f4_normal, f4_uv;
		for (GMint i = 0; i < 2; i++)
		{
			for (GMint j = 0; j < 3; j++) // j表示面的一个顶点
			{
				GMint idx = i * 3 + j; //顶点的开始
				GMint idx_next = i * 3 + (j + 1) % 3;
				GMint idx_prev = i * 3 + (j + 2) % 3;
				GMVec2 uv(uvArr[indices[idx] * 2], uvArr[indices[idx] * 2 + 1]);
				GMVec3 vertex(t[indices[idx] * 3], t[indices[idx] * 3 + 1], t[indices[idx] * 3 + 2]);
				GMVec3 vertex_prev(t[indices[idx_prev] * 3], t[indices[idx_prev] * 3 + 1], t[indices[idx_prev] * 3 + 2]),
					vertex_next(t[indices[idx_next] * 3], t[indices[idx_next] * 3 + 1], t[indices[idx_next] * 3 + 2]);
				GMVec3 normal = Cross(vertex - vertex_prev, vertex_next - vertex);
				normal = FastNormalize(normal);

				vertex.loadFloat4(f4_vertex);
				normal.loadFloat4(f4_normal);
				uv.loadFloat4(f4_uv);

				GMVertex v = {
					{ f4_vertex[0], f4_vertex[1], f4_vertex[2] },
					{ f4_normal[0], f4_normal[1], f4_normal[2] }
				};

				if (customUV)
				{
					v.texcoords[0] = f4_uv[0];
					v.texcoords[1] = 1 - f4_uv[1];
				}
				else
				{
					v.texcoords[0] = (f4_uv[0] + 1) / 2;
					v.texcoords[1] = 1 - (f4_uv[1] + 1) / 2;
				}
				v.color[0] = v.color[1] = v.color[2] = v.color[3] = 1.f;
				body->vertex(v);
			}
		}
		if (shaderCallback)
			shaderCallback->onCreateShader(model->getShader());
	}

	*obj = model;
}

void GMToolUtil::createTexture(const GMString& filename, ITexture** texture)
{
	gm::GMImage* img = nullptr;
	gm::GMBuffer buf;
	GM.getGamePackageManager()->readFile(gm::GMPackageIndex::Textures, filename, &buf);
	gm::GMImageReader::load(buf.buffer, buf.size, &img);
	GM_ASSERT(img);

	GM.getFactory()->createTexture(img, texture);
	GM_ASSERT(texture);
	gm::GM_delete(img);
}

void GMToolUtil::addTextureToShader(gm::GMShader& shader, ITexture* texture, GMTextureType type, GMuint index)
{
	GM_ASSERT(index < GMMaxTextureCount(type));
	auto& frames = shader.getTexture().getTextureFrames(type, index);
	frames.addFrame(texture);
}