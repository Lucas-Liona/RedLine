#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
#include <functional>

struct Point {
    const int x;
    const int y;
    Point(int x_, int y_): x(x_), y(y_) {};
};

Point qrs_xy(int q, int r, int s, int radius, int xoffset, int yoffset);

struct HexData {
    const int x;
    const int y;
    const int occupancy; // by num of rails in hexagon, starts from 0 and ++
                        // if greater than 1, create a terminal on hexagon
};

struct Hex {
    const int q;
    const int r;
    const int s;
    Hex(int q_, int r_, int s_): q(q_), r(r_), s(s_) {
        if (q + r + s != 0) throw "q + r + s must be 0";
    }
    
    bool operator==(const Hex& h) const {
        return(q == h.q && r == h.r && s == h.s);
    }
};

bool equalTo(Hex a, Hex b);
int order(Hex a);
Hex hex_add(Hex a, Hex b);
Hex hex_subtract(Hex a, Hex b);
Hex hex_rotate_left(Hex a);
Hex hex_rotate_right(Hex a);

// Forward declaration of common_elements to resolve circular dependency
std::vector<Hex> common_elements(std::vector<Hex> a, std::vector<Hex> b);

namespace std {
    template <> struct hash<Hex> {
        size_t operator()(const Hex& h) const {
            hash<int> int_hash;
            size_t hq = int_hash(h.q);
            size_t hr = int_hash(h.r);
            return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
        }
    };
}

struct Grid {
    const std::vector<Hex> hex_grid;
    const int ord;
    
    Grid(int order): ord(order) {}
};

extern const std::vector<Hex> hex_directions;
Hex hex_direction(int direction);
