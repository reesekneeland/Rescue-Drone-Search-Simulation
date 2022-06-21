#include<memory>
#include<vector>
#include "filter.h"
#include "image.h"
#ifndef INVERT_FILTER_H_
#define INVERT_FILTER_H_

using namespace std;

class InvertFilter : public Filter {
    public:
        /**
        * @brief Default constructor for Invert Filter.
        * @return Nothing.
        */
        InvertFilter();
        /**
        * @brief Apply Invert Filter.
        * @param original Original image.
        * @param filtered Filtered image.
        * @return Nothing.
        */
        void Apply(vector<Image *> original, vector<Image *> filtered);

    private:
        
    
};

#endif
