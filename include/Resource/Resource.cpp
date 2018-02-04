#include "Resource.h"
#include "DxLib.h"


//Graph::Graph(int h) :
//	handle(h)
//{}

int GraphFactory::CreateGraph(string fileName) {
	int handle = LoadGraph(fileName.c_str());
	return handle;
}

int GraphFactory::GetGraph(string fileName) {
	auto it = pool.find(fileName);
	if (it != pool.end())
		return it->second;
	int newGraph = CreateGraph(fileName);
	pool.insert(make_pair(fileName, newGraph));
	return newGraph;
}