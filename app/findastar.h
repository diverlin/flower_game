#ifndef FINDASTAR_H
#define FINDASTAR_H

#include <vector>

namespace core {

int findPathAStar(const int nStartX, const int nStartY,
                  const int nTargetX, const int nTargetY,
                  const int* pMap, const int nMapWidth, const int nMapHeight,
                  std::vector<int>& outBuffer);

} // namespace core

#endif // FINDASTAR_H

