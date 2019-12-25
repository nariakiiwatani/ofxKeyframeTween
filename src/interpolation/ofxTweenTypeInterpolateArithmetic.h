#pragma once

#include "ofxTweenLite.h"

namespace ofx { namespace tweentype { namespace interpolate {
	
	template<typename Type>
	struct Numeric {
		static inline int dim();
		static inline Type getInterpolated(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease);
	};
	
	template<> inline int Numeric<bool>::dim() { return 1; }
	template<> inline bool Numeric<bool>::getInterpolated(float k, float k0, float k1, const bool &v0, const bool &v1, std::vector<ofEaseFunction> ease) {
		return ofxTweenLite::tween(v0?1:-1, v1?1:-1, ofMap(k,k0,k1,0,1), ease[0]) >= 0;
	}
	
#define IMPL_ARITH(Type) \
template<> inline int Numeric<Type>::dim() { return 1; } \
template<> inline Type Numeric<Type>::getInterpolated(float k, float k0, float k1, const Type &v0, const Type &v1, std::vector<ofEaseFunction> ease) {\
return ofxTweenLite::tween(v0, v1, ofMap(k,k0,k1,0,1), ease[0]);\
}
	IMPL_ARITH(char)
	IMPL_ARITH(short)
	IMPL_ARITH(int)
	IMPL_ARITH(long)
	IMPL_ARITH(long long)
	IMPL_ARITH(unsigned char)
	IMPL_ARITH(unsigned short)
	IMPL_ARITH(unsigned int)
	IMPL_ARITH(unsigned long)
	IMPL_ARITH(unsigned long long)
	IMPL_ARITH(float)
	IMPL_ARITH(double)
#undef IMPL_ARITH
	
}}}
