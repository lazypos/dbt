#ifndef _h_common_H_
#define _h_common_H_

template <typename T>
class CMySingleton
{
public:
	CMySingleton() {};
	~CMySingleton() {};

	static T* Instance() {
		static T t;
		return &t;
	}
};

#endif