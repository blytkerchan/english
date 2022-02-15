#ifndef vlinder_english_poet_hpp
#define vlinder_english_poet_hpp

#include "english-export.h"
#include <string>
#include <vector>

namespace Vlinder { namespace English {
std::string createPoem(std::vector< unsigned char > const &data) english_EXPORT;
}}

#endif
