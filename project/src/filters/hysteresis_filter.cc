#include "hysteresis_filter.h"
#include "image.h"

void HysteresisFilter::Apply(std::vector<Image*> original,std::vector<Image*> filtered){
    *filtered[0]=*original[0];
    int width = original[0]->GetWidth();
    int height = original[0]->GetHeight();
    for(int x = 0; x < width; x++){//go from 1 to width and height -2 to avoid hitting edge of the image
        for(int y = 0; y < height; y++){
            unsigned char* pixel = original[0]->GetPixel(x,y);
            if(pixel[0] == WEAK && pixel[1] == WEAK && pixel[2] == WEAK){
                
                unsigned char* left = original[0]->GetOverflowPixel(x-1,y); //get the surrounding pixels
                unsigned char* right = original[0]->GetOverflowPixel(x+1,y);
                unsigned char* up = original[0]->GetOverflowPixel(x,y+1);
                unsigned char* down=original[0]->GetOverflowPixel(x,y-1);
                unsigned char* diagonalUpLeft=original[0]->GetOverflowPixel(x-1,y+1);
                unsigned char* diagonalUpRight=original[0]->GetOverflowPixel(x+1,y+1);
                unsigned char* diagonalDownLeft=original[0]->GetOverflowPixel(x-1,y-1);
                unsigned char* diagonalDownRight=original[0]->GetOverflowPixel(x+1,y-1);

                //check for at least 1 string pixel
                if((left[0] == STRONG && left[1] == STRONG && left[2] == STRONG)||
                (right[0] == STRONG && right[1] == STRONG && right[2] == STRONG)||
                (up[0] == STRONG && up[1] == STRONG && up[2] == STRONG)||(down[0] == STRONG && down[1] == STRONG && down[2] == STRONG)||
                (diagonalUpLeft[0] == STRONG && diagonalUpLeft[1] == STRONG && diagonalUpLeft[2] == STRONG)||
                (diagonalUpRight[0] == STRONG && diagonalUpRight[1] == STRONG && diagonalUpRight[2] == STRONG)||
                (diagonalDownLeft[0] == STRONG && diagonalDownLeft[1] == STRONG && diagonalDownLeft[2] == STRONG)||
                (diagonalDownRight[0] == STRONG && diagonalDownRight[1] == STRONG && diagonalDownRight[2] == STRONG)){

                    unsigned char strong [4] {(unsigned char)STRONG,(unsigned char)STRONG,(unsigned char)STRONG,255};
                    filtered[0]->SetPixel(x,y,strong);//make current weak pixel strong
                }

                else{//if there are no strong pixels we'll make it black to remove noise

                    unsigned char black[4] = {0,0,0,255};
                    filtered[0]->SetPixel(x,y,black);
                }
            }
        }
    }
}