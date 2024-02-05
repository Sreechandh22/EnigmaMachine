/*
Author: Sreechandh Devireddy
Date: 10/31/23
Description: Thsi is the main fn file for this assignment. It first checks the number of arguements passed by the user and if it is under the minimum it prints out an error, it foes from there with a bunch of if else ststements to check for the number of arguements passes and also the charecters passed by the user(i.e -i, -e, -d and so on). It then builds the rotor, sets it to the position and then encrypts and decrypts the charecters.
Usage: devireddy_sreechandh_assn3.c
*/

#include <stdio.h>                  //The standard input/output library
#include "rotorMachine.h"           //custom header file
#include <string.h>                 //string handling library

int main(int argc, char *argv[])    //the main fn that takes 2 args
{ 

int rotor1[28];                     //declares 2 int arrays with 28 elemenst each
int rotor2[28];

    if (argc < 3)                   //Checks the number of cmd line args is less than 3
    { 
        printf("Usage Error\n");    //If so it prints an error message
    } 
    else if (argc == 3 && strcmp(argv[1], "-i")== 0)    //if there are exactly 3 args and the second args is -i 
    { 
        buildIni(argv[2]);          //then it calls the buildIni to initialise the rotor config
    } 
    else if (argc == 7 || argc == 9)    //if the cmd line args is either 7 or 9 
    {   
        if(argc == 9)               //if the cmd line args is 9
        { 
            if (strcmp(argv[7], "-i") == 0) 
            {
                buildIni(argv[8]);

                if(strcmp(argv[4],"-r") ==0) 
                {
                    FILE *infile = fopen(argv[2], "r");     //opens the input files
                    FILE *outfile = fopen(argv[3], "w");    //opens th eputput file

                    int rotations1 = atoi(argv[5]);         //converts the rotation args to ints and initialises teh rotors
                    int rotations2 = atoi(argv[6]);
                    buildRotors(rotor1, rotor2);
                    setRotor1(rotor1, rotations1);
                    setRotor2(rotor2, rotations2);

                    if(strcmp(argv[1],"-e") == 0)           //calls the appropruate fn to encrypt or decrypt the file based on the cmd line artgs passed
                    {
                        encryptFile(infile, outfile, rotor1, rotor2);   //encrypt sthat file
                    } 
                    else if( strcmp(argv[1], "-d") == 0) 
                    {
                        decryptFile(infile, outfile, rotor1, rotor2);   //decrypt sthat file
                    }
                 }
            }
        } 
        else if( argc == 7)                         //if the user passes 7 cmd line args
        {
            if(strcmp(argv[4],"-r") ==0) 
            {
                FILE *infile = fopen(argv[2], "r");     //iopens teh input file
                FILE *outfile = fopen(argv[3], "w");    //opens the putput file

                int rotations1 = atoi(argv[5]);         //converts the rotation args to int and initialises teh rotors
                int rotations2 = atoi(argv[6]);
                buildRotors(rotor1, rotor2);
                setRotor1(rotor1, rotations1);
                setRotor2(rotor2, rotations2);

                if(strcmp(argv[1],"-e") == 0)       //calls the appropriate fn to encrypt or decrypt teh file basd on th cmd line args
                {
                    encryptFile(infile, outfile, rotor1, rotor2);       //encrypt sthat file
                } 
                else if( strcmp(argv[1], "-d") == 0) 
                {
                    decryptFile(infile, outfile, rotor1, rotor2);       //decrypt sthat file
                }
            }
        }
    }
}