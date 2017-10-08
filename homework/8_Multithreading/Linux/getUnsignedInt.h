#ifndef GETUNSIGNEDINT_H
#define GETUNSIGNEDINT_H

//function that return only read from user characters from keyboyard and return only unsinged int
//parameters:
//nFrom - low number margin
//nTo   - upper number margin
//sInvitationMessage - text invitation string in in ostream will be returned this merssage and ranges of number i.e. nFrom and nTo
//sRangeErrorMeesage - text error string that will be displayed if entered number is in not diapazone between nFrom nTo

unsigned int getUnsignedInt(unsigned int nFrom, unsigned int nTo, const char * sInvitationMessage, const char * sRangeErrorMessage);

#endif // GETUNSIGNEDINT_H
