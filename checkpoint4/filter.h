#include<memory>
#include<vector>
#include "image.h"
#ifndef FILTER_H_
#define FILTER_H_

using namespace std;

class Filter {
    public:
        Filter() {};
        
        virtual void Apply(vector<Image *> original, vector<Image *> filtered) = 0;

    private:
        
    
};

#endif
