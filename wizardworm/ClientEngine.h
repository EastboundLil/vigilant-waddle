#pragma once
#include "IEngine.h"
class ClientEngine :
	public IEngine
{
public:
	ClientEngine();
	~ClientEngine();

	std::vector<Data> GenerateMoveset();
};

