# /*
# Author: Sreechandh Devireddy
# Date: 10/31/23
# Description: thsi file comiles and links the encryption and decryption system.
# Usage: makeFile make [all|clean]
# */

CC = g++							#The C compiler to be  used

CFLAGS = -Wall -g					# #Flags for the C compiler

all: rotorMachine

rotorMachine: rotorMachine.o devireddy_sreechandh_assn3.o
	$(CC) $(CFLAGS) $^ -o $@

rotorMachine.o: rotorMachine.c rotorMachine.h
	$(CC) $(CFLAGS) -c $<

devireddy_sreechandh_assn3.o: devireddy_sreechandh_assn3.c rotorMachine.h		#This line specifies that the devireddy_sreechandh_assn3.c depends on rotorMachine
	$(CC) $(CFLAGS) -c $<

clean:											#This clean target removes all the -o files and maikes our main fiel executable
	rm -f rotorMachine *.o

