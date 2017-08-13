#ifndef CSU_UTILITIES_HPP
#define CSU_UTILITIES_HPP

#include <utility>
#include <list>

namespace CSU { namespace Utilities {
    void packRects(std::list<std::pair<unsigned int, std::pair<unsigned int, unsigned int>>> &rects, unsigned int &resultW, unsigned int &resultH);
}}
#endif // CSU_UTILITIES_HPP
