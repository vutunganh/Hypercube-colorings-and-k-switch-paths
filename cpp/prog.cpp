#include "hypercube.hpp"
#include "generators.hpp"

#include <cstdio>
#include <chrono>

int main(void)
{
  fprintf(stderr, "MAX_VERTEX: %d.\n", MAX_VERTEX);
  const auto begin = std::chrono::steady_clock::now();
  Coloring c = 0;
  do {
    for (int v = 0; v < (1 << (N - 1)); ++v) {
      printf("%d ", findLeastSwitchGeodesic(v, c));
    }
    puts("");
  } while (nextColoring(c, c));
  const auto end = std::chrono::steady_clock::now();
  fprintf(stderr, "Time: %ld ms.\n",
          std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count());
  return 0;
}
