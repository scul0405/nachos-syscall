#include "syscall.h"

int main() {
	int ping2, pong2;

	PrintString("Pingpong is running.\n");
	
	ping2 = Exec("./test/ping2");
	pong2 = Exec("./test/pong2");

	Join(ping2);
	Join(pong2);
}
