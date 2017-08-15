#include "ClassArraySample.h"
#include <dirent.h> 
#include <iostream>

int main()
{

    DIR           *d;
    struct dirent *dir;
    d = opendir("/home/alexex/test/data/train/train/");
    if (d)
    {
    while ((dir = readdir(d)) != NULL)
    {
      std::cout << dir->d_name << endl;
    }

    closedir(d);
    }


    ClassArraySample a[5];
    a[0].addElementVector(14);
    a[0].addElementVector(22);
    a[0].addElementVector(244);
    
    std::cout << a[0];
    return 0;
}
