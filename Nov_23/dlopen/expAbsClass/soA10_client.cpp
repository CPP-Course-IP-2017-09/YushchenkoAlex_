//client.c
#include <stdio.h>
#include <dlfcn.h>
#include "BaseA.h"
#include <iostream>
using namespace std;

//g++ -Wall -fPIC -shared -o libgetA10.so -std=c++11 server.h server.cpp BaseA.h A10.h A10.cpp
//g++ -rdynamic -o client -std=c++11 BaseA.h soA10_client.cpp -ldl

int main(int argc, char **argv) 
{
   void *lib_handle;
   typedef BaseA * (*GetFactoryT)(char * sCatName, int * pLength);
   int x;
   char *error;

	lib_handle = dlopen("./libgetA10.so", RTLD_LAZY);
   if (!lib_handle) 
   {
      fprintf(stderr, "cannot open library!! %s\n", dlerror());
		cout<<"libgetA10.so"<<endl;
      return 1;//exit(1);
   }
	cout<<"Library was loaded"<<endl;

   GetFactoryT pfn = (GetFactoryT) dlsym(lib_handle, "GetFactory");
   if ((error = dlerror()) != NULL)  
   {
      fprintf(stderr, "ERROR!! cannot get GetFactory func%s\n", error);
      dlclose(lib_handle);
      return 1;//exit(1);
   }
	cout<<"function was received"<<endl;
	int nSize = 10;
	char sName[10];

	BaseA * pBaseA = 0;
	pBaseA = (*pfn)(sName, &nSize);
   printf("===  =========================\n");
	cout<<"Mult "<<pBaseA->Mult(5, 8)<<endl;
	pBaseA->Destroy();
   dlclose(lib_handle);
   printf("enter a number = after unload =\n");
	scanf("%d", &x);
   printf("===  %d =========================\n", x);

   return 0;
}
