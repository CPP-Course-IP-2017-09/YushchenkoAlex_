#include <iostream>

#include "client.h"

int main()
{   

    Client client;

    std::cout<<client->getFileName()<<std::endl;

    return 0;
}
