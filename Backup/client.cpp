#include <iostream>

#include "client.h"
#include "backupwithcheck.h"
#include <string.h>

#include "testhandler.h"

#define SIZE 10
typedef int TYPE;

//constructor
Client::Client():m_pBackup(NULL)
{
    m_pBackup = new BackupWithCheck("./backups/myBackup");

    //create array and filling
    TYPE * pFirstArray = new TYPE [SIZE];

    for(int i=0;i<SIZE;++i)
        pFirstArray[i] = i;

    //write backup
    std::cout<<"Making backup..."<<std::endl;
    m_pBackup->write(pFirstArray,sizeof(TYPE)*SIZE);
    std::cout<<"Making backup:"<<m_pBackup->getStatusMessage()<<std::endl;

    TYPE * pSecondArray = new TYPE [m_pBackup->getBytes()];
    unsigned int nSecondArrayBytes = 0;

    //try to restore backup
    std::cout<<"Restoring backup..."<<std::endl;
    m_pBackup->read(pSecondArray,&nSecondArrayBytes);
    std::cout<<"Restoring backup result:"<<m_pBackup->getStatusMessage()<<std::endl;

    //show backuped array
    std::cout<<"Current array:"<<std::endl;
    for(int i=0;i<SIZE;++i)
        std::cout<<pFirstArray[i]<<"\t";
    std::cout<<std::endl;

    //show backuped array
    std::cout<<"Backuped array:"<<std::endl;
    for(int i=0;i<SIZE;++i)
        std::cout<<pSecondArray[i]<<"\t";
    std::cout<<std::endl;

    delete [] pFirstArray;
    delete [] pSecondArray;
                                                                                                                                                                                                            Test(std::cout<<this<<" Client() m_pBackup: "<<m_pBackup<<std::endl;)
}

//destructor
Client::~Client()
{
    if(m_pBackup != NULL)
        delete m_pBackup;
                                                                                                                                                                                                             Test(std::cout<<this<<" ~Client()"<<std::endl;)
}

//access to backup
BackupWithCheck * Client::operator->()
{
    return (BackupWithCheck *)m_pBackup;
}
