#include "syscall.h"

int main() {
	int ping, pong;
	PrintString("Pingpong is running.");
	
	ping = Exec("./test/ping");
	pong = Exec("./test/pong");
	Join(ping);
	PrintChar('C');
	Join(pong);
	PrintChar('D');
	Halt();
}
