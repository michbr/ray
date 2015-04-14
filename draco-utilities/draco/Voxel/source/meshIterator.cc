
#include "meshIterator.h"

using namespace std;
using namespace Vox;


MeshIterator::MeshIterator(Tree* tree, const Index& startPos): tree(tree), pos(0) {
    while(pos.depth<startPos.depth) {
        traverse(pos.directionTo(startPos));
    }
}

void MeshIterator::traverse(byte i) {
    pos = pos.getChild(i);
    blocks[1][1][1] = &blocks[1][1][1]->getBlock(i);
//    Node* parentNodes[2][2][2];
//    byte xOff = (i &4) >> 2;
//    byte yOff = (i &2) >> 1;
//    byte zOff = i &1;
//    for(byte x=0; x<2; ++x) {
//        for(byte y=0; y<2; ++y) {
//            for(byte z=0; z<2; ++z) {
//                parentNodes[x][y][z] = nodes[x +xOff][y +yOff][z +zOff];
//            }
//        }
//    }
//    
//    for(byte x=0; x<DIMMENSION; ++x) {
//        for(byte y=0; y<DIMMENSION; ++y) {
//            for(byte y=0; y<DIMMENSION; ++y) {
//                nodes[]
//            }
//        }
//    }
}

