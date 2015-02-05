#include "thread.h"

using namespace std;

Thread::Thread(Runnable * r) {
	toRun = r;
}

void Thread::start() {
	t = new thread(callRun, toRun);
}

void Thread::callRun(Runnable * runner) {
	runner->run();
}
