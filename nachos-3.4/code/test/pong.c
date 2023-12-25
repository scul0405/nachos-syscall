#include "syscall.h"

int main() {
	int i;
	for (i = 0; i < 1000; i++) {
		Down("pong");
		PrintChar('B');
		Up("ping");
	}
	Halt();
}
