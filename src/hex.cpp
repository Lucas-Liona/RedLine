#include "hex.h"
#include <vector>
#include <algorithm>
#include <math.h>

const std::vector<Hex> hex_directions = {
    Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1), 
    Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
};

Point qrs_xy(int q, int r, int s, int radius, int xoffset, int yoffset)
{
    int x = (int) (xoffset + 1.5*radius*q);
    int y = (int) (yoffset + sqrt(3)*(radius*r/2 - radius*s/2));
    
    return(Point(x, y));
}

bool equalTo(Hex a, Hex b) {
    return(a.q == b.q && a.r == b.r && a.s == b.s);
}

int order(Hex a) 
{
    return(std::max({abs(a.q), abs(a.r), abs(a.s)}));
}

Hex hex_add(Hex a, Hex b)
{
    return Hex(a.q + b.q, a.r + b.r, a.s + b.s);
}

Hex hex_subtract(Hex a, Hex b)
{
    return Hex(a.q - b.q, a.r - b.r, a.s - b.s);
}

Hex hex_rotate_left(Hex a)
{
    return Hex(-a.s, -a.q, -a.r);
}

Hex hex_rotate_right(Hex a)
{
    return Hex(-a.r, -a.s, -a.q);
}

Hex hex_direction(int direction)
{
    return hex_directions[direction];
}

std::vector<Hex> common_elements(std::vector<Hex> a, std::vector<Hex> b) {
    std::vector<Hex> arr;
    
    for(size_t i = 0; i < a.size(); i++) {
        for(size_t j = 0; j < b.size(); j++) {
            if(a[i] == b[j]) {
                arr.push_back(a[i]);
            }
        }
    }
    
    return(arr);
}
