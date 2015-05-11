#pragma once

#include <list>
#include "NodeState.h"

class Node
{
public:
    
    Node(const int x, const int y);
	Node(const int x, const int y, bool isBlock);		//se isBlock==true allora è un blocco invalicabile
    
    inline int X() const { return aiCoord[0]; }
    inline int Y() const { return aiCoord[1]; }
    
    bool operator==(const Node &other) const
    {
        return X() == other.X() && Y() == other.Y();
    }
    
    NodeState           eState;
    Node*               pParent;
    int                 iF;
    int                 iG;
    int                 iH;
    std::list<Node*>    lAdj;
    
private:
    int                 aiCoord[2];
};
