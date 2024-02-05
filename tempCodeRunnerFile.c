/*
Author: Sreechandh Devireddy
Date: 10/30/23
Description: This file has a C program to implement a rotor based encryptio and decryption system. it includes various functions to handle diferrent aspects pf teh process. The program uses teh functions below to read the confurigations, perform encrytion and decryption on files and manage the state of the rotors.
Usage: rotorMachine.c
*/

#include <stdio.h>                          //these are all teh inclusions that include teh dependencies
#include "rotorMachine.h"                   //this is the custon heade file inclusion
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ROTOR_SIZE 28                       //defines macros, for the rotor size and teh buffer size
#define BUFFER_SIZE 256
#ifndef ENCRYPT_FILE_DEFINED
#define ENCRYPT_FILE_DEFINED

void buildRotors(int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);
void rotateRotorRight(int rotor[ROTOR_SIZE]);
void rotateRotorLeft(int rotor[ROTOR_SIZE]);
int charToIndex(char convert);
char indexToChar(int convert);
void encryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);
void decryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]);


int main(){

    printf("Before start:\n");
    int rotor1[28];
    int rotor2[28];

    buildRotors(rotor1, rotor2);
    setRotor1(rotor1, 5);
    setRotor2(rotor2, 5);

    FILE *infile = fopen("C://Users//sreec//OneDrive//Desktop//Homework3//test.txt","r");         //Opens the rotors.ini file in read mode(r), and stores the file pointer in inFile
    FILE *outfile = fopen("C://Users//sreec//OneDrive//Desktop//Homework3//output.txt", "w");    

    encryptFile(infile, outfile, rotor1, rotor2);

    printf("After start:\n");
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
        exit(1);                                //Exits away from te program with a non-szero status code
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

void rotateRotor(int rotor[], int size, int direction)  //Thsi fn taskes an array, its sir and the direction inorder to rotate
{
    int temp;                                           //A temporary variable to hold the val that shall be moved later            
    if (direction == 1)                                 //If direction is 1 rotate right
    {  
        temp = rotor[size - 1];                         //Stores the last element in temp
        for (int i = size - 1; i > 0; i--)              //This loop will now shofts all elements to right
        {
            rotor[i] = rotor[i - 1];                    
        }
        rotor[0] = temp;                                //placesthe lasy ele in the first pos
    } 
    else if (direction == -1)                           //if the dir is -1 turn left
    {  
        temp = rotor[0];
        for (int i = 0; i < size - 1; i++) 
        {
            rotor[i] = rotor[i + 1];
        }
        rotor[size - 1] = temp;
    }
}


void encryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE]) 
{
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, infile) != NULL)  // this while loop reads every line-by-line
    {
        for (int i = 0; i < (int)strlen(buffer) ; ++i)  // this processess each character in the line
        {
            char ch = buffer[i];

            // Encrypt the character
            int index1 = charToIndex(ch);  // here we convert the character to its index in rotor1
            int value1 = rotor1[index1];  // now we get the corresponding value from rotor1

            int index2;
            for (index2 = 0; index2 < ROTOR_SIZE; ++index2)  // now we find the index in rotor2 that matches value1
            {
                if (rotor2[index2] == value1){
                    break;
                }  
            }

            char encryptedChar = indexToChar(index2);  // we can convert the index back to a character
            fputc(encryptedChar, outfile);  // we write the encrypted character to the output file

            rotateRotorRight(rotor1);           // Rotate the rotors
            rotateRotorLeft(rotor2);
        }
        fprintf(outfile, "\n");  // Add a newline after processing each line
    }
}

void decryptFile(FILE *infile, FILE *outfile, int rotor1[ROTOR_SIZE], int rotor2[ROTOR_SIZE])       //this fn takes input and output file poimters amd 2 arrays
{
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, infile) != NULL)          //here agian the while and for loops read each encrypted char from the int file decrypt it using yhe rotors and write the decrypted char to the out file
    {
        for (int i = 0; i < (int)strlen(buffer) ; ++i) 
        {
            char ch = buffer[i];
            if (ch == '\n')                                     //If the charecter is equal to a new line
            {
                fputc(ch, outfile);
                continue;
            }
            int index = charToIndex(ch);
            int rotor2Value = rotor2[index % ROTOR_SIZE];
            int rotor1Index;
            for (rotor1Index = 0; rotor1Index < ROTOR_SIZE; ++rotor1Index)
            {
                if (rotor1[rotor1Index] == rotor2Value)
                    break;
            }
            char decryptedChar = indexToChar(rotor1Index);      // we can convert the index back to a character
            fputc(decryptedChar, outfile);

            rotateRotorRight(rotor1);               //rotates the rotors after each char
            rotateRotorLeft(rotor2);
        }
                fprintf(outfile, "\n");  // Add a newline after processing each line
    } 
}


#endif
