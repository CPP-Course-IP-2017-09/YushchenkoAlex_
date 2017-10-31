#include <stdio.h>
#include <string.h>
#include <iostream>
#include <errno.h>

#include "generalbackup.h"
#include "testhandler.h"
#include "BACKUP_STATUSES.h"



GeneralBackup::GeneralBackup(const char * sFileName):m_sFileName(NULL), m_nBytes(0), m_pVoid(NULL),m_sStatusMessage(NOT_DONE)
{ 

        //memory allocation
        m_sFileName = new char [(strlen(sFileName) + 1)];

        //copy file name inside backup
        strcpy(m_sFileName,sFileName);

        //end of string flag setup
        m_sFileName[strlen(sFileName)] = '\0';
                                                                                                                                                                                                                    Test(std::cout<<this<<" GeneralBackup() "<<" m_pVoid: "<<m_pVoid<<" m_nBytes: "<<m_nBytes<<" sFileName: "<<m_sFileName<<std::endl;);
}

//destructor
GeneralBackup::~GeneralBackup()
{
    if(m_sFileName != NULL)
    {
        delete [] m_sFileName;
    }
                                                                                                                                                                                                                     Test(std::cout<<this<<" ~GeneralBackup() "<<std::endl;);
}


/*---------------------------------------------getFuncctions()---------------------------------------------*/

//return size of backup
unsigned int GeneralBackup::getBytes()
{
    return m_nBytes;
}

//return file name
const char * GeneralBackup::getFileName()
{
    return m_sFileName;
}

const char * GeneralBackup::getStatusMessage()
{
    return m_sStatusMessage;
}

/*---------------------------------------------setFuncctions()---------------------------------------------*/

//return errno error code
int GeneralBackup::setFileName(const char * sFileName)
{
    //open file for backup with write binary permissions
    FILE * fBackup = fopen(sFileName,"wb");

    if (fBackup == NULL)
    {
        perror("Error:");
    }
    else
    {
        //closing file
        fclose (fBackup);

        //delete old file name
        if(m_sFileName != NULL)
            delete m_sFileName;

        //memory allocation for new file name
        m_sFileName = new char [(strlen(sFileName) + 1)];

        //copy file name inside backup
        strcpy(m_sFileName,sFileName);

        //end of string flag setup
        m_sFileName[strlen(sFileName)] = '\0';
    }
                                                                                                                                                                                             Test(std::cout<<this<<" GeneralBackup::setFileName("<<sFileName<<"), m_sFileName: "<<m_sFileName<<", error code: "<<errno<<" ("<<strerror(errno)<<")"<<std::endl;);
   return errno;
}
