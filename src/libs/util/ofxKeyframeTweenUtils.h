#pragma once

#include <vector>

namespace ofx { namespace tweentype { namespace utils {
template<typename hasDim, typename T = ofEaseFunction>
static inline std::vector<T> makeVectorFor(const T &t) {
	return std::vector<T>(hasDim::dim(), t);
}
}}}