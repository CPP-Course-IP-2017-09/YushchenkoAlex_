// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SERVERVS_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SERVERVS_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SERVERVS_EXPORTS
#define SERVERVS_API __declspec(dllexport)
#else
#define SERVERVS_API __declspec(dllimport)  // for implicit linkage
#endif

// This class is exported from the serverVS.dll
class SERVERVS_API CserverVS {
public:
	CserverVS(void);
	// TODO: add your methods here.
};

extern SERVERVS_API int nserverVS;

SERVERVS_API int fnserverVS(void);
extern "C" SERVERVS_API int Mult(int a, int b);