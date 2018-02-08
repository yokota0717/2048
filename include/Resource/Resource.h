#pragma once
#include <map>
#include <string>
#include <memory>

using namespace std;


//class Graph {
//	int handle;
//
//public:
//	Graph(int);
//};

//class GraphFactory {
//	map<string, int> pool;
//
//	int CreateGraph(string);
//
//public:
//	int GetGraph(string);
//};

class GraphFactory {
	map<string, int> pool;

	int CreateGraph(const char*);

public:
	int GetGraph(const char*);
};