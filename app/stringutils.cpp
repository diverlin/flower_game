#include "stringutils.h"

namespace core {
namespace stringutils {

std::string replace(const std::string& src, const std::string& search, const std::string& replace)
{
    std::string result(src);
    size_t pos = result.find(search);
    if (pos != std::string::npos) {
        result.replace(pos, search.length(), replace);
    }
    return result;
}

} // namespace stringutils
} // namescore core

