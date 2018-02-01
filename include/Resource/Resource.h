#pragma once
#include <map>
#include <string>
#include <memory>

using namespace std;


class Graph {
	int handle;

	Graph(int);
};

class GraphFactory {
	map<string, shared_ptr<Graph>> pool;

	shared_ptr<Graph> CreateGraph(string);

public:
	shared_ptr<Graph> GetGraph(string);
};