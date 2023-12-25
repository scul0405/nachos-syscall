#include "syscall.h"

int main() {
	int ping, pong;
	
	if(CreateSemaphore("ping",0) == -1)	return 1;
	if(CreateSemaphore("pong",1) == -1)	return 1;

	PrintString("Pingpong is running.\n");
	
	ping = Exec("./test/ping");
	pong = Exec("./test/pong");

	Join(ping);
	Join(pong);
}
