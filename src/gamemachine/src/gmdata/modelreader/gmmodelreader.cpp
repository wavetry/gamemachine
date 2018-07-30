﻿#include "stdafx.h"
#include "gmmodelreader.h"
#include "gmmodelreader_obj.h"
#include "gmmodelreader_md5mesh.h"
#include "gmdata/gamepackage/gmgamepackage.h"
#include "foundation/gamemachine.h"

class GMModelReaderContainer : public GMObject
{
public:
	GMModelReaderContainer()
	{
		m_readers[GMModelReader::Object] = new GMModelReader_Obj();
		m_readers[GMModelReader::Md5Mesh] = new GMModelReader_MD5Mesh();
	}

	~GMModelReaderContainer()
	{
		for (auto iter = m_readers.begin(); iter != m_readers.end(); iter++)
		{
			GM_delete(iter->second);
		}
	}

	IModelReader* getReader(GMModelReader::ModelType type)
	{
		GM_ASSERT(m_readers.find(type) != m_readers.end());
		return m_readers[type];
	}

private:
	Map<GMModelReader::ModelType, IModelReader*> m_readers;
};

IModelReader* GMModelReader::getReader(ModelType type)
{
	static GMModelReaderContainer readers;
	return readers.getReader(type);
}

GMModelReader::ModelType GMModelReader::test(const GMBuffer& buffer)
{
	for (ModelType i = ModelType_Begin; i < ModelType_End; i = (ModelType)((GMuint)i + 1))
	{
		if (getReader(i)->test(buffer))
			return i;
	}
	return ModelType_End;
}

bool GMModelReader::load(const GMModelLoadSettings& settings, OUT GMModels** models)
{
	return load(settings, Auto, models);
}

bool GMModelReader::load(const GMModelLoadSettings& settings, ModelType type, OUT GMModels** models)
{
	GMBuffer buffer;
	if (settings.type == GMModelPathType::Relative)
		GM.getGamePackageManager()->readFile(GMPackageIndex::Models, settings.filename, &buffer);
	else
		GM.getGamePackageManager()->readFileFromPath(settings.filename, &buffer);

	if (type == Auto)
		type = test(buffer);

	if (type == ModelType_End)
		return false;

	return getReader(type)->load(settings, buffer, models);
}
