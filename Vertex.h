#pragma once
struct Vertex
{
protected:
	int _id;

public:
	virtual void connect(Vertex v);
};

void Vertex::connect(Vertex v)
{
	//
}

