#include "Resource.h"
#include "DxLib.h"


Graph::Graph(int h):
	handle(h)
{}

shared_ptr<Graph> GraphFactory::CreateGraph(string fileName) {
	int handle;
	handle = LoadGraph(fileName.c_str());
	auto newGraph = make_shared<Graph>(handle);
	return newGraph;
}

shared_ptr<Graph> GraphFactory::GetGraph(string fileName) {
	auto it = pool.find(fileName);
	if (it != pool.end())
		return it->second;
	auto newGraph = CreateGraph(fileName);
	pool.insert(make_pair(fileName, newGraph));
	return newGraph;
}
