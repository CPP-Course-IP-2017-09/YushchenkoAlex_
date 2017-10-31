#include "backup.h"
#include "testhandler.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "errno.h"

//constructor
Backup::Backup(const char * sFileName):GeneralBackup(sFileName)
{

                                                                                                                                                                                                                    Test(std::cout<<this<<" Backup() "<<" m_pVoid: "<<m_pVoid<<" m_nBytes: "<<m_nBytes<<" sFileName: "<<m_sFileName<<std::endl;);
}

//destructor
Backup::~Backup()
{
                                                                                                                                                                                                                     Test(std::cout<<this<<" ~Backup() "<<std::endl;);
}

/*----------------------------read() & write() functions----------------------------*/

//read backup, return errno error code
bool Backup::read(void * pV, unsigned int * p_nBytes)
{
    unsigned int nReadBytes = 0;

    //open file for backup with read binary permissions
    FILE * fBackup = fopen(m_sFileName,"rb");

    if (fBackup == NULL)
    {
        perror("Error:");
        m_sStatusMessage = strerror(errno);
        return false;
    }
    else
    {
        //reading bytes from file
        nReadBytes = fread(pV,1,m_nBytes,fBackup);
        fclose (fBackup);

        *p_nBytes = nReadBytes;
    }
                                                                                                                                                                                                                          Test(;std::cout<<this<<" Backup::read("<<pV<<", "<<p_nBytes<<"), nReadBytes: "<<nReadBytes<<", fBackup: "<<fBackup<<", error code: "<<errno<<" ("<<strerror(errno)<<")"<<std::endl;);
    return true;
}

//write backup, return errno error code
bool Backup::write(const void * pV, int nBytes)
{
    unsigned int nWroteBytes = 0;

    //open file for backup with write binary permissions
    FILE * fBackup = fopen(m_sFileName,"wb");

    if (fBackup == NULL)
    {
        perror("Error:");
        m_sStatusMessage = strerror(errno);
        return false;
    }
    else
    {
        //writing bytes into file
        nWroteBytes = fwrite(pV,1,nBytes,fBackup);
        fclose (fBackup);

        //saving size of backup
        m_nBytes = nWroteBytes;
    }
                                                                                                                                                                                                                            Test(;std::cout<<this<<" Backup::write("<<pV<<", "<<nBytes<<"), nWroteBytes: "<<nWroteBytes<<", fBackup: "<<fBackup<<", error code: "<<errno<<" ("<<strerror(errno)<<")"<<std::endl;);
   m_sStatusMessage = strerror(errno);

   return true;
}


