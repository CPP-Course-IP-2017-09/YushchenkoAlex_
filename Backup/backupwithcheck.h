#ifndef BACKUPWITHCHECK_H
#define BACKUPWITHCHECK_H

#include "backup.h"

class BackupWithCheck: public Backup
{
public:
    BackupWithCheck(const char * sFileName);            //constructor
    virtual ~BackupWithCheck();                                 //destructor


// read() & write() functions
    virtual bool write(const void * pV, int nBytes);     //write backup, return errno error code
};

#endif // BACKUPWITHCHECK_H
