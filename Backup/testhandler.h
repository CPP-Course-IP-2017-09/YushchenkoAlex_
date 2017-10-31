#ifndef TESTHANDLER_H
#define TESTHANDLER_H

//#define TEST_ON
#define TEST_OFF

#ifdef TEST_ON
//#define BACKUP_WITH_CHECK_TEST

#define Test(parameter) parameter
#endif


#ifdef TEST_OFF
#define Test(parameter)
#endif

#ifdef BACKUP_WITH_CHECK_TEST
#define BackupWithCheckTestTest(parameter) parameter
#endif

#ifndef BACKUP_WITH_CHECK_TEST
#define BackupWithCheckTestTest(parameter)
#endif


#endif  // TESTHANDLER_H
