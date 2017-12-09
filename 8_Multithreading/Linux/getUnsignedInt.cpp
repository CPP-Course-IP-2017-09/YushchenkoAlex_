#include <iostream>
#include <stdio.h>
#include "getUnsignedInt.h"
#include "getch.h"

#ifdef __linux__
#define BACKSPACE 127
#define BSPACE '\b'
#define END_OF_LINE '\n'
#endif

#ifdef _WIN32
#define BACKSPACE 8
#define BSPACE (char)8
#define END_OF_LINE (char)13
#endif


unsigned int getUnsignedInt(unsigned int nFrom, unsigned int nTo, const char *sInvitationMessage, const char * sRangeErrorMessage)
{

unsigned int nBufferSize = 1;

for(unsigned int i = 1; i < nTo; i *= 10)
  nBufferSize++;

//pointer to constant for preventing change unsigned int buffer size, it value will be acording to ranges from argument
const unsigned int * P_UNSIGNED_INT_BUFFER_SIZE = & nBufferSize;

//returned value in the beginning equal to NULL
int nNumber = 0;

//current index of sNumber char array in the beginning equal to 0
unsigned int iCurInd = 0;

//char array memory dedication
char sNumber[ * P_UNSIGNED_INT_BUFFER_SIZE] = {0};

//char symbol buffer variable for getting symbols via my_getch() function
char a;


std::cout<<sInvitationMessage<<" (from "<<nFrom<<" to "<<nTo<<"):";


//first loop check nNumber according to ranges
//second loop get symbols from stdin

while(true)
  {
    while(true)
      {

        //getting symbol
        a = my_getch();

        //if symbol is digit code it will be showed and added to sNumber
        if(a>='0' && a<='9')
          {
            //checking size overload according to range 1 additional symbol for "\0"
            if(iCurInd < * P_UNSIGNED_INT_BUFFER_SIZE - 1)
              {
                std::cout<<a;
                sNumber[iCurInd++] = a;
              }
          }
        //backspace
        else if(a == BACKSPACE)
          {
            if(iCurInd != 0)
              {
                --iCurInd;
                sNumber[iCurInd] = 0;

                std::cout<<BSPACE;
                std::cout<<' ';
                std::cout<<BSPACE;
              }
          }
        //if enter pressed
        else if(a == END_OF_LINE && iCurInd != 0)
          {
            //converting char array to int value
            nNumber = atoi(sNumber);
            std::cout<<std::endl;

            //exit from second loop loop
            break;
          }
     }

    //if nNumber out of range
    if(nNumber < nFrom || nNumber > nTo)
      {
        std::cout<<std::endl<<sRangeErrorMessage<<std::endl;
        std::cout<<sInvitationMessage<<" (from "<<nFrom<<" to "<<nTo<<"):";

        //null flushing sNumber
        for(int i=0; i < * P_UNSIGNED_INT_BUFFER_SIZE; ++i)
            sNumber[i] = 0;
        iCurInd = 0;
      }
    else
      {
        return nNumber;
      }
    }
  }
