#ifndef BACKUP_H
#define BACKUP_H

#include "generalbackup.h"

class Backup: public GeneralBackup
{
protected:
    Backup(const Backup & Right);               //copy constructor
    Backup & operator=(const Backup & Right);   //assignment operator

public:
    Backup(const char * sFileName);             //constructor
    virtual ~Backup();                                  //destructor

// read() & write() functions
    bool read(void * pV, unsigned int *p_nBytes);       //read backup, return errno error code
    virtual bool write(const void * pV, int nBytes);    //write backup, return errno error code
};

#endif // BACKUP_H
