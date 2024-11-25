#ifndef CHECK_H
#define CHECK_H
#include <stdlib.h>
class Check{
public:
    void ClearSystem(){
        system(
            #ifdef _WIN32
                "cls"
            #else
                "clear"
            #endif
        );
    }
};
#endif