/**
 * @file Point.hpp
 * @brief Header file for the Point class - A class that will help us save a position on the game board.
 * The position is given as two double coordinates that keep the position of the unit along the x and y axes accordingly.
 * @author Tomer Gozlan
 * @date 11/05/2023 
 */

#ifndef COWBOY_VS_NINJA_A_POINT_HPP
#define COWBOY_VS_NINJA_A_POINT_HPP

#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

namespace ariel {

    class Point {

    private:
        double coordinate_x;
        double coordinate_y;
    public:

        Point(double coordinate_x, double coordinate_y);

        double distance(Point &other);

        void print();

        Point moveTowards(Point& source, Point& dest, double distance);
    };
}

#endif //COWBOY_VS_NINJA_A_POINT_HPP