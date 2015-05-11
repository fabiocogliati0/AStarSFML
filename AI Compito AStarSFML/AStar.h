#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <list>
#include "Node.h"

class AStar
{
public:

	AStar();

	static int getXMax();

	static int getYMax();

	sf::Color getNodeColor(int x, int y) const;

	bool SearchFinished() const;

	void SetBlockMap(bool* map);

	void Init();

	void Update();

	void Clean();

private:
    const static int xMax = 10;
    const static int yMax = 10;
    const static int iStartNode = 0;
    const static int iEndNode = 99;
    
	void CleanBlockMap();
    void CreateGraph();
    void CreateGraphAdjs();
    void CreateNodeAdj(const int iRow, const int iCol);
    
    void ComputeGraphHeuristics();
    void ComputeNodeHeuristic(Node* pNode);
   
    Node* VisitNode();
    void AddNodeToOpenList(Node* pParent, Node* pNode);
    
    void PrintPath(Node* pNode) const;
    
    Node* tRoot[xMax * yMax];

	bool bBlockMap[xMax * yMax];
    
    std::list<Node*> qOpenList;
};
