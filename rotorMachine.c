/*
Author: Sreechandh Devireddy
Date: 10/31/23
Description: This file has a C program to implement a rotor based encryptio and decryption system. it includes various functions to handle diferrent aspects pf teh process. The program uses teh functions below to read the confurigations, perform encrytion and decryption on files and manage the state of the rotors.
Usage: rotorMachine.c
*/

#include <stdio.h>                          //these are all teh inclusions that include teh dependencies
#include "rotorMachine.h"                   //this is the custon heade file inclusion
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


void setRotor1(int rotor[ROTOR_SIZE], int rotations) 
{
    for (int i = 0; i < rotations; ++i)     //Loopps rotatiosn a bunch of times
    {
     rotateRotorRight(rotor);               //Calls the fn to rotate the rotor to thr igth
    }
}

void setRotor2(int rotor[ROTOR_SIZE], int rotations) 
{
    for (int i = 0; i < rotations; ++i)     //Loops teh rotations a number of timea
    {
        rotateRotorLeft(rotor);             //Calls the fn to rotate the rotor to left
    }
}


void buildIni(const char *filename)         //This fn reads the confurigation file, it has a pointer to the filename
{
    FILE *configFile = fopen(filename, "r");    //opens the file in a read mode
    
    
    if (configFile == NULL)  //this is thsi error handling statemnt, it checks if the either of teh files are null
    {
        printf("Error! In buildIni ");                      //If indeed it is null, it prints an error statemnt
        // exit(1);                                //And exits the program
    }
    
    int buildvalue;                             //declares this variable, to store our int
    // int count = 0;                              //INTITIALISES THIS VARIABLE TO 0, we need this to keep track of the number of integers passes
    FILE *iniFile = fopen("rotors.ini", "w");   //also opens a new  file ins a writing mode
    while (fscanf(configFile, "%d", &buildvalue) == 1)      //thsi while loop continues as long as our fscanf reads an integer from configFile and stores it in buildvalue.
    {
        buildvalue=buildvalue^42;                       //XOR's each integer with 42
        fprintf(iniFile, "%d\n", buildvalue);   //writes the int to teh file
    }
    fclose(configFile);                         //closes yhe config file    
    fclose(iniFile);                            //closes the initialisation file
}

void buildRotors(int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]) 
{
    FILE *iniFile = fopen("rotors.ini", "r");         //Opens the rotors.ini file in read mode(r), and stores the file pointer in inFile
    if (iniFile == NULL)                        //Checks if teh file opened is null inside
    {   
        printf("Error!.\n");                   //Incase it is null and cant be opned it shows an error message (easy to understand for our reference)
        // exit(1);                                //Exits away from te program with a non-szero status code
    }
    int value;                                  //thos variable is declared inorder to store the values read from teh file
    for (int i = 0; i < ROTOR_SIZE; ++i)        //We loop through each element in rotor1
    {
        fscanf(iniFile, "%d", &value);          //Reads an int from teh file and stores it in a value
        rotor1[i] = value ^ 42;                 //XOR's teh values and stores it in rotor1
    }
    for (int i = 0; i < ROTOR_SIZE; ++i)        //Now we loop through each element in rotor 2
    {
        fscanf(iniFile, "%d", &value);          //Reads an int from teh file and stores in a value
        rotor2[i] = value ^ 42;                 //xOR'S TEH VALue with 42 and stores in rotor2
    }
    fclose(iniFile);                            //Finally we close the file
}


void rotateRotorRight(int rotor[ROTOR_SIZE])    
{
    int last = rotor[ROTOR_SIZE - 1];       //Here we store the last element of the array
    for (int i = ROTOR_SIZE - 1; i > 0; --i)    //Loops through the array from teh right
    {
        rotor[i] = rotor[i - 1];            //Shifts each element to right
    }
    rotor[0] = last;                        //We now set the first element to the stored last element
}

void rotateRotorLeft(int rotor[ROTOR_SIZE]) 
{
    int first = rotor[0];                   //Stores the first element of teh array
    for (int i = 0; i < ROTOR_SIZE - 1; ++i) //Loops through teh srray  from left to right
    {
        rotor[i] = rotor[i + 1];            //Shifts each element to left
    }
    rotor[ROTOR_SIZE - 1] = first;          //Sets last ele to teh stored first ele
}


int charToIndex(char convert)           
{
    convert = toupper(convert);            //To convert the chars to uppercaase
    if (convert == ' ')                     //If teh char is a space
        return 26;                          //we retuen 26
    if (convert == '.')                     //If a char is a fullstop
        return 27;                          //we return 27
    return (int)convert - 65;               //here we convert teh char to its ASCii valus nd then to it index in teh alphabet
}

char indexToChar(int convert) 
{
    if (convert == 26)                      //Checks if the index is 25
        return ' ';                         //return a space
    if (convert == 27)                      //If the index is a 27
        return '.';                         //return a fullstop
    return (char)(convert + 65);            //converst index to its matching ASCII char
}



void encryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]) 
{
    char ch; 
    while ((ch = fgetc(infile)) != EOF)  // Read line-by-line
    {

        if(ch == '\n'){          
            fputc(ch, outfile);
            continue;
        }

        // Encrypt the character
        int index1 = charToIndex(ch);  // Convert the character to its index in rotor1
        int value1 = rotor1[index1];  // Get the corresponding value from rotor1

        int index2;
        int k = 0;
        for (index2 = 0; index2 < 28; ++index2)  // Find the index in rotor2 that matches value1
        {
            if (rotor2[index2] == value1){
                k = index2;
                break;
            }  
        }

        char encryptedChar = indexToChar(k);  // Convert the index back to a character
        fputc(encryptedChar, outfile);  // Write the encrypted character to the output file

        // Rotate the rotors
        rotateRotorRight(rotor1);
        rotateRotorLeft(rotor2);
    }
}

void decryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE])       //this fn takes input and output file poimters amd 2 arrays
{
    char ch; 
    while ((ch = fgetc(infile)) != EOF)  // Read line-by-line
    {

        if(ch == '\n'){          
            fputc(ch, outfile);
            continue;
        }

        // Encrypt the character
        int index1 = charToIndex(ch);  // Convert the character to its index in rotor1
        int value1 = rotor2[index1];  // Get the corresponding value from rotor1

        int index2;
        int k = 0;
        for (index2 = 0; index2 < 28; ++index2)  // Find the index in rotor2 that matches value1
        {
            if (rotor1[index2] == value1){
                k = index2;
                break;
            }  
        }

        char encryptedChar = indexToChar(k);  // Convert the index back to a character
        fputc(encryptedChar, outfile);  // Write the encrypted character to the output file

        // Rotate the rotors
        rotateRotorRight(rotor1);
        rotateRotorLeft(rotor2);
    }
}
