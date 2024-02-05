/*
Author: Sreechandh Devireddy
Date: 10/31/23
Description: This C file defines a rotor machine for file encryption and decryption. It includes fns for building rotors, rotating them, and converting to chars to indices.
Usage: rotorMachine.h [-i config_file] [-e input_file output_file] [-d input_file output_file]
*/

#ifndef ROTOR_MACHINE_DEFINED           //These are the include guards
#define ROTOR_MACHINE_DEFINED

#include <stdio.h>                      //these are the standard library inclusions
#include <stdlib.h>
#include <ctype.h>

#define ROTOR_SIZE 28                   // define constants for rotor size
#define BUFFER_SIZE 256                 //defines constant for buffer size 
#define XOR_VALUE 42                    //defines constant for Xor value

void buildIni(const char *filename);                                    //The below lines declare prototypes for all the various fns used in this assignment
void buildRotors(int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);
void rotateRotorRight(int rotor[ROTOR_SIZE]);
void rotateRotorLeft(int rotor[ROTOR_SIZE]);
void setRotor1(int rotor[ROTOR_SIZE], int rotations);
void setRotor2(int rotor[ROTOR_SIZE], int rotations);
int charToIndex(char convert);
char indexToChar(int convert);
void encryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);
void decryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);      //this fn takes input and output file poimters amd 2 arrays

#endif