#include <CSE/CSU/utilities.hpp>

#include <utility>
#include <list>

#include <cmath>

namespace CSU { namespace Utilities {
    static bool rectCmp(std::pair<unsigned int, std::pair<unsigned int, unsigned int>> A,
                        std::pair<unsigned int, std::pair<unsigned int, unsigned int>> B) {
        if (A.second.second > B.second.second) {
            return true;
        } else if (A.second.second < B.second.second) {
            return false;
        } else {
            if (A.second.first > B.second.first) {
                return true;
            } else if (A.second.first < B.second.first) {
                return false;
            }
            return false;
        }
    }

    void packRects(std::list<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &rects,
                   unsigned int &resultW, unsigned int &resultH) {
        rects.sort(rectCmp);

        std::list<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>>::iterator it;

        float area;

        for (it = rects.begin(); it != rects.end(); ++it) {
            area += it->second.first * it->second.second;
        }

        unsigned int dims = (unsigned int) std::ceil(std::sqrt(area));
        // above gets us the power of two that would contain everything assuming area
        // was PERFECTLY tightly packed (ie: dissecting rects up allowed)

        unsigned int xMark = 0;
        unsigned int yMark = 0;
        unsigned int yTemp = 0;

        for (it = rects.begin(); it != rects.end(); ++it) {
            if (xMark + it->second.first > dims) {
                xMark = 0;
                yMark += yTemp;
                yTemp = 0;
            }
            xMark += it->second.first;
            yTemp = std::max(yTemp, it->second.second);
        }
        yMark += yTemp;
        resultW = dims;
        resultH = yMark;
    }
}}
