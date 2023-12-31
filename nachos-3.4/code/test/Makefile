# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = ../../../gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B../../../gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)

all: halt shell matmult sort help ascii char string num createfile ping pong pingpong main sinhvien voinuoc ping2 pong2 pingpong2

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

num.o: num.c
	$(CC) $(CFLAGS) -c num.c
num: num.o start.o
	$(LD) $(LDFLAGS) start.o num.o -o num.coff
	../bin/coff2noff num.coff num
help.o: help.c 
	$(CC) $(CFLAGS) -c help.c 
help: help.o start.o 
	$(LD) $(LDFLAGS) start.o help.o -o help.coff 
	../bin/coff2noff help.coff help

ascii.o: ascii.c 
	$(CC) $(CFLAGS) -c ascii.c 
ascii: ascii.o start.o 
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff 
	../bin/coff2noff ascii.coff ascii
char.o: char.c
	$(CC) $(CFLAGS) -c char.c
char: char.o start.o
	$(LD) $(LDFLAGS) start.o char.o -o char.coff
	../bin/coff2noff char.coff char

string.o: string.c
	$(CC) $(CFLAGS) -c string.c
string: string.o start.o
	$(LD) $(LDFLAGS) start.o string.o -o string.coff
	../bin/coff2noff string.coff string

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

ping.o: ping.c
	$(CC) $(CFLAGS) -c ping.c
ping: ping.o start.o
	$(LD) $(LDFLAGS) start.o ping.o -o ping.coff
	../bin/coff2noff ping.coff ping

pong.o: pong.c
	$(CC) $(CFLAGS) -c pong.c
pong: pong.o start.o
	$(LD) $(LDFLAGS) start.o pong.o -o pong.coff
	../bin/coff2noff pong.coff pong

pingpong.o: pingpong.c
	$(CC) $(CFLAGS) -c pingpong.c
pingpong: pingpong.o start.o
	$(LD) $(LDFLAGS) start.o pingpong.o -o pingpong.coff
	../bin/coff2noff pingpong.coff pingpong

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
main: main.o start.o
	$(LD) $(LDFLAGS) start.o main.o -o main.coff
	../bin/coff2noff main.coff main

voinuoc.o: voinuoc.c
	$(CC) $(CFLAGS) -c voinuoc.c
voinuoc: voinuoc.o start.o
	$(LD) $(LDFLAGS) start.o voinuoc.o -o voinuoc.coff
	../bin/coff2noff voinuoc.coff voinuoc

sinhvien.o: sinhvien.c
	$(CC) $(CFLAGS) -c sinhvien.c
sinhvien: sinhvien.o start.o
	$(LD) $(LDFLAGS) start.o sinhvien.o -o sinhvien.coff
	../bin/coff2noff sinhvien.coff sinhvien

ping2.o: ping2.c
	$(CC) $(CFLAGS) -c ping2.c
ping2: ping2.o start.o
	$(LD) $(LDFLAGS) start.o ping2.o -o ping2.coff
	../bin/coff2noff ping2.coff ping2

pong2.o: pong2.c
	$(CC) $(CFLAGS) -c pong2.c
pong2: pong2.o start.o
	$(LD) $(LDFLAGS) start.o pong2.o -o pong2.coff
	../bin/coff2noff pong2.coff pong2

pingpong2.o: pingpong2.c
	$(CC) $(CFLAGS) -c pingpong2.c
pingpong2: pingpong2.o start.o
	$(LD) $(LDFLAGS) start.o pingpong2.o -o pingpong2.coff
	../bin/coff2noff pingpong2.coff pingpong2
