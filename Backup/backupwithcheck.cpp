#include <iostream>
#include <string.h>

#include "backupwithcheck.h"
#include "BACKUP_STATUSES.h"
#include "testhandler.h"

#define ERROR_CODE -1

//constructor
BackupWithCheck::BackupWithCheck(const char * sFileName):Backup(sFileName)
{
Test(std::cout<<this<<" BackupWithCheck() "<<" m_pVoid: "<<m_pVoid<<" m_nBytes: "<<m_nBytes<<" sFileName: "<<m_sFileName<<std::endl;);
}

//destructor
BackupWithCheck::~BackupWithCheck()
{
Test(std::cout<<this<<" ~BackupWithCheck()"<<std::endl;);
}


/*----------------------------read() & write() functions----------------------------*/

//write backup, return errno error code
bool BackupWithCheck::write(const void * pV, int nBytes)
{
    unsigned int nWroteBytes = 0;

    //open file for backup with write binary permissions
    FILE * fBackup = fopen(m_sFileName,"wb");

    if (fBackup == NULL)
    {
        perror("Error:");
    }
    else
    {
        //writing bytes into file
        nWroteBytes = fwrite(pV,1,nBytes,fBackup);
        fclose (fBackup);

        //saving size of backup
        m_nBytes = nWroteBytes;

        //creating temp array for checking
        char * pTemp = new char [nBytes];
                                                                                                                                                                                                                                                                                                    BackupWithCheckTestTest(int temp;std::cin>>temp;)
        //read what we wrote from file
        fBackup = fopen(m_sFileName,"rb");

        if (fBackup == NULL)
        {
            perror("Error:");
        }
        else
        {
            int nReadBytes = fread(pTemp,1,nBytes,fBackup);

            if(nBytes != nReadBytes)
            {                                                                                                                                                                                                                                                                                       Test(std::cout<<this<<" BackupWithCheck::write("<<pV<<", "<<nBytes<<"), nWroteBytes: "<<nWroteBytes<<", fBackup: "<<fBackup<<", error code: "<<errno<<" ("<<strerror(errno)<<") result: "<<NOT_COMPLETED<<std::endl;);
                m_sStatusMessage = NOT_COMPLETED;
                delete [] pTemp;
                return false;
            }
            else
            {
                //comparing two arrays
                char * pVTemp = (char *)pV;
                if(strncmp(pTemp,pVTemp,nBytes) == 0)
                {                                                                                                                                                                                                                                                                                   Test(std::cout<<this<<" BackupWithCheck::write("<<pV<<", "<<nBytes<<"), nWroteBytes: "<<nWroteBytes<<", fBackup: "<<fBackup<<", error code: "<<errno<<" ("<<strerror(errno)<<") result: "<<strerror(errno)<<std::endl;);
                    m_sStatusMessage = strerror(errno);
                    delete [] pTemp;
                    return true;
                }
                else
                {                                                                                                                                                                                                                                                                                   Test(std::cout<<this<<" BackupWithCheck::write("<<pV<<", "<<nBytes<<"), nWroteBytes: "<<nWroteBytes<<", fBackup: "<<fBackup<<", error code: "<<errno<<" ("<<strerror(errno)<<") result: "<<IS_DAMAGED<<std::endl;);
                    m_sStatusMessage = IS_DAMAGED;
                    delete [] pTemp;
                    return false;
                }

            }
        }

        delete [] pTemp;

    }
                                                                                                                                                                                                                                                                                                    Test(;std::cout<<this<<" Backup::write("<<pV<<", "<<nBytes<<"), nWroteBytes: "<<nWroteBytes<<", fBackup: "<<fBackup<<", error code: "<<errno<<" ("<<strerror(errno)<<")"<<std::endl;);
   m_sStatusMessage = strerror(errno);

   return false;
}
