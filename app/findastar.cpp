#include "findastar.h"

#include <queue>
#include <cmath>
#include <climits>
#include <tuple>
#include <iostream>

namespace core {

int findPathAStar(const int nStartX, const int nStartY,
                  const int nTargetX, const int nTargetY,
                  const int* pMap, const int nMapWidth, const int nMapHeight,
                  std::vector<int>& outBuffer)
{
    //std::cout << "from="+std::to_string(nStartX)+","+std::to_string(nStartY) << std::endl;
    //std::cout << "to="+std::to_string(nTargetX)+","+std::to_string(nTargetY) << std::endl;

    auto idx = [nMapWidth](int x, int y) {
        return x + y*nMapWidth;
    };

    auto h = [=](int u) -> int { // lower bound distance to target from u
        int x = u % nMapWidth, y = u / nMapWidth;
        return std::abs(x-nTargetX) + std::abs(y-nTargetY);
    };

    const int n = nMapWidth*nMapHeight;
    const int startPos = idx(nStartX, nStartY);
    const int targetPos = idx(nTargetX, nTargetY);

    int discovered = 0;
    //int ExploredNodes = 0;
    std::vector<int> p(n), d(n, INT_MAX);
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>,
                        std::greater<std::tuple<int, int, int>>> pq; // A* with tie breaking
    d[startPos] = 0;
    pq.push(std::make_tuple(0 + h(startPos), 0, startPos));
    while (!pq.empty()) {
        int u = std::get<2>(pq.top());
        pq.pop();
        //ExploredNodes++;
        for (auto e : {+1, -1, +nMapWidth, -nMapWidth}) {
            int v = u + e;
            if ((e == 1 && (v % nMapWidth == 0)) || (e == -1 && (u % nMapWidth == 0)))
                continue;
            if (0 <= v && v < n && d[v] > d[u] + 1 && !pMap[v]) {
                p[v] = u;
                d[v] = d[u] + 1;
                if (v == targetPos)
                    goto end;
                pq.push(std::make_tuple(d[v] + h(v), ++discovered, v));
            }
        }
    }
end:

    if (d[targetPos] == INT_MAX) {
        return -1;
    } else {
        int curr = targetPos;
        for (int i = d[targetPos] - 1; i >= 0; i--) {
            outBuffer.push_back(curr);
            curr = p[curr];
        }

        //        for (int i=0; i<nMapHeight*nMapWidth; ++i) {
        //            std::cout << "map[" + std::to_string(i) + "]=" + std::to_string(m_map[i]) << std::endl;
        //        }
        //        for (int i=0; i<nOutBufferSize; ++i) {
        //            std::cout << "out[" + std::to_string(i) + "]=" + std::to_string(pOutBuffer[i]) << std::endl;
        //        }

        return d[targetPos];
    }

    std::cout << "ERROR: buffer size too small" << std::endl;
    return d[targetPos]; // buffer size too small
}

} // namespace core
