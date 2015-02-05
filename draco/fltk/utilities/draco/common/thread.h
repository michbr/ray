#ifndef DRACO_THREADS_OBJ
#define DRACO_THREADS_OBJ

#include <thread>

class Runnable {
public:
        virtual void run() = 0;

};

class Thread {
private:
	std::thread * t;
	Runnable * toRun;
	static void callRun(Runnable * runner);
public:
	Thread (Runnable * r);
	void start();
};

#endif
