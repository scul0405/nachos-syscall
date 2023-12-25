#include "syscall.h"

int main() {
	int i;
	for (i = 0; i < 1000; i++) {
		Down("ping");
		PrintChar('A');
		Up("pong");
	}
	Halt();
}
