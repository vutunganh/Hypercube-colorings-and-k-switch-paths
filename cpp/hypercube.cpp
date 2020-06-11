#include "hypercube.hpp"

#include <algorithm>
#include <limits>
#ifdef DEBUG
#include <cassert>
#endif /* DEBUG */

bool
isEdgeRed(const Coloring& c, const Edge& e)
{
  return c & (1 << e);
}

template<int N>
struct OneToNArray
{
  constexpr OneToNArray()
    : A()
  {
    for (int i = 0; i < N; ++i) {
      A[i] = 1 + i;
    }
  }

  int A[N];
};

int
findLeastSwitchGeodesic(const Vertex v, const Coloring& c)
{
  OneToNArray A = OneToNArray<N>();
  int res = std::numeric_limits<int>::max();

  do {
    int cur = 0;
    Vertex prevVertex = v;
    Edge prevEdge = encodeEdge(v, A.A[0]);
    for (int i = 1; i < N - 1; ++i) {
      const Vertex curVertex = prevVertex ^ directionMask(decodeDirection(prevEdge));
      const Edge curEdge = encodeEdge(curVertex, A.A[i]);
      #ifdef DEBUG
      const Direction d = decodeDirection(prevEdge);
      fprintf(stderr, "Previous vertex: %d.\n", prevVertex);
      fprintf(stderr, "Previous edge: %d.\n", prevEdge);
      fprintf(stderr, "Current vertex: %d.\n", curVertex);
      fprintf(stderr, "Current direction, current masked direction: %d, %d.\n", A.A[i], directionMask(A.A[i]));
      fprintf(stderr, "Current edge: %d.\n", curEdge);
      fputc('\n', stderr);
      assert(1 <= d && d <= N);
      #endif /* DEBUG */
      if (isEdgeRed(c, prevEdge) ^ isEdgeRed(c, curEdge)) {
        ++cur;
      }
      prevVertex = curVertex;
      prevEdge = curEdge;
    }
    res = std::min(cur, res);
  } while (std::next_permutation(A.A, A.A + N));

  return res;
}
