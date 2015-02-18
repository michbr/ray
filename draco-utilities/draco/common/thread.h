#ifndef DRACO_THREADS_OBJ
#define DRACO_THREADS_OBJ

#include "EXPORT.h"
#include <thread>


class Runnable {
public:
	DRACO_COMMON_API virtual void run() = 0;

};

class Thread {
private:
	std::thread * t;
	Runnable * toRun;
	static void callRun(Runnable * runner);
public:
	DRACO_COMMON_API Thread (Runnable * r);
	DRACO_COMMON_API void start();
};

#endif
