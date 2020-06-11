#ifndef __GENERATORS__
#define __GENERATORS__

#include "hypercube.hpp"

Vertex
incrementVertex(const Vertex v);

Direction
incrementDirection(const Direction d);

/**
 * Returns true if an edge larger than `e` in our ordering exists. The result is
 * stored in `result`. The output `result` is undefined if the function returns
 * `false`.
 */
bool
nextEdge(const Edge e, Edge& result);

bool
nextColoring(const Coloring& c, Coloring& result);

#endif /* __GENERATORS__ */
