#ifndef CLIENT_H
#define CLIENT_H

#include "backupwithcheck.h"

class Client
{
    GeneralBackup * m_pBackup;
    Client(const Client & Right);               //copy cosntructor
    Client & operator=(const Client & Right);   //assginment operator
public:
    Client();                                   //constructor
    ~Client();                                  //destructor
    BackupWithCheck * operator->();             //access to backup
};

#endif // CLIENT_H
