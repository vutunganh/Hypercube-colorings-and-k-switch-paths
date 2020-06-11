#include "generators.hpp"

Vertex
incrementVertex(const Vertex v)
{
  if (MAX_VERTEX == v) {
    return 0;
  }

  return 1 + v;
}

Direction
incrementDirection(const Direction d)
{
  if ((1 << (N - 1)) == d) {
    return 1;
  }

  return d << 1;
}

bool
nextEdge(const Edge e, Edge& result)
{
  if (MAX_EDGE == e) {
    return false;
  }

  Vertex v = decodeVertex(e);
  Direction d = decodeDirection(e);
  if (MAX_VERTEX == v) {
    result = encodeEdge(incrementVertex(v), incrementDirection(d));
  }

  result = encodeEdge(incrementVertex(v), d);
  return true;
}

bool
nextColoring(const Coloring& c, Coloring& result)
{
  if (c == 1ll << ( N * (1 << (N - 1)))) {
    return false;
  }

  result = 1 + c;
  return true;
}
