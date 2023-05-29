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

        double getX() const;

        double getY() const;

        void setX(double newX);

        void setY(double newY);

        double distance(const Point &other) const;

        std::string print() const;

        static Point moveTowards(const Point &source, const Point &dest, double distance);

    };
}

#endif //COWBOY_VS_NINJA_A_POINT_HPP