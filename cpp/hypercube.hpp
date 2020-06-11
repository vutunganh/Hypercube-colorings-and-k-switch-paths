#ifndef __HYPERCUBE__
#define __HYPERCUBE__

#include <limits>
#include <bitset>
#include <cstdint>

const int N = 3;

using Vertex = int;
// Numbers in binary from 1 up to N. E.g. for Q_4 `Direction` can be 1 := 0001,
// 2 := 0010, 3 := 0100, 4 := 1000.
using Direction = int;
using Edge = int;
using Coloring = int64_t;

inline extern constexpr Vertex MAX_VERTEX =
  (~0u << (std::numeric_limits<Vertex>::digits - N)) >>
  (std::numeric_limits<Vertex>::digits - N + 1);
inline extern constexpr Vertex MAX_DIRECTION = N;

constexpr Direction
directionMask(const int d)
{
  return 1 << (d - 1);
}

/**
 * Given a pair of vertex `v` and direction `d` it returns an encoding of such
 * pair as follows: 0...0{d in binary}{v}.
 */
constexpr Edge
encodeEdge(const Vertex v, const Direction d)
{
  return (d << N) | (v & ~directionMask(d));
}

inline extern constexpr Vertex MAX_EDGE = encodeEdge(MAX_VERTEX, MAX_DIRECTION);

constexpr Vertex
decodeVertex(const Edge e)
{
  constexpr Edge vertexMask = MAX_VERTEX;
  return e & vertexMask;
}

constexpr Vertex
decodeDirection(const Edge e)
{
  constexpr Edge directionMask = MAX_VERTEX << N;
  return (e & directionMask) >> N;
}

constexpr Vertex
antipodalVertex(const Vertex v)
{
  constexpr Vertex vertexMask = MAX_VERTEX;
  return v ^ vertexMask;
}

constexpr Vertex
otherEndOfEdge(const Vertex v, const Edge e)
{
  const Direction d = decodeDirection(e);
  return v ^ directionMask(d);
}

bool
isEdgeRed(const Coloring& c, const Edge& e);

int
findLeastSwitchGeodesic(const Vertex v, const Coloring& c);

#endif /* __HYPERCUBE__ */
