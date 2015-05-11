#include "Node.h"

Node::Node(const int x, const int y) : eState(NodeState::Unknown),
                                        iF(0),
                                        iG(0),
                                        iH(0)
{
    aiCoord[0] = x;
    aiCoord[1] = y;
}

Node::Node(const int x, const int y, bool isBlock) : Node(x,y)
{
	if (isBlock)
	{
		eState = NodeState::Block;
	}
	else
	{
		eState = NodeState::Unknown;
	}
}