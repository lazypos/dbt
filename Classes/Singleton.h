#ifndef _CSINGLETON_H_
#define _CSINGLETON_H_

template <typename T>
class CSingleton {
	CSingleton() {};

public:
	static T* instance() {
		static T myT;
		return &myT;
	}
};

#endif