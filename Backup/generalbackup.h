#ifndef GENERALBACKUP_H
#define GENERALBACKUP_H


class GeneralBackup
{
protected:
    void * m_pVoid;
    int    m_nBytes;
    char * m_sFileName;
    char * m_sStatusMessage;

public:
    GeneralBackup(const char *sFileName);        //constructor
    ~GeneralBackup();                             //destructor

//getFuncctions()
    unsigned int getBytes();                   //return size of backup
    const char * getFileName();                //return file
    const char * getStatusMessage();           //return status of backup

//setFunctions()
    int setFileName(const char * sFileName);  //return errno error code

// read() & write() functions virtual
    virtual bool read(void * pV, unsigned int *p_nBytes) = 0;       //read backup,  return true if ok, or false if not ok (see getStatusMessage())
    virtual bool write(const void * pV, int nBytes)      = 0;       //write backup, return true if ok, or false if not ok (see getStatusMessage())
};

#endif // GENERALBACKUP_H
