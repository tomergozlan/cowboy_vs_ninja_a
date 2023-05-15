/**
 * @file Point.cpp
 * @brief A class for representing a position on a 2D game board.
 * @author Tomer Gozlan
 * @date 11/05/2023
 */

#include "Point.hpp"

namespace ariel {
/**
 * @brief Constructs a new Point object with the given x and y coordinates.
 * @param x The x coordinate.
 * @param y The y coordinate.
 * @throws std::invalid_argument if the coordinates are NaN, infinite, or out of bounds.
 */
    Point::Point(double coordinate_x, double coordinate_y) {
        if (std::isnan(x) || std::isnan(y)) {
            throw std::invalid_argument("Invalid coordinates: NaN values not allowed.");
        }
        if (std::abs(x) > DBL_MAX || std::abs(y) > DBL_MAX) {
            throw std::out_of_range("Invalid coordinates: Out of bounds.");
        }
        this->coordinate_x=x;
        this->coordinate_y=y;
    }
/**
* @brief Returns the x coordinate of this position.
* @return The x coordinate of this position.
*/
    double Point::getX() const {
        return this->coordinate_x;
    }

/**
* @brief Returns the y coordinate of this position.
*
* @return The y coordinate of this position.
*/
    double Point::getY() const {
        return this->coordinate_y;
    }

/**
 * @brief Set the x-coordinate of the point.
 * @param newX The new value for the x-coordinate.
 * @throw std::invalid_argument if newX is NaN (not a number).
 * @throw std::out_of_range if newX is out of bounds.
 */
    void Point::setX(double newX) {
        if (std::isnan(newX)) {
            throw std::invalid_argument("Invalid coordinates: NaN values not allowed.");
        }
        if (std::abs(newX) > DBL_MAX) {
            throw std::out_of_range("Invalid coordinates: Out of bounds.");
        }
        this->coordinate_x=newX;
    }

/**
 * @brief Set the y-coordinate of the point.
 * @param newY The new value for the y-coordinate.
 * @throw std::invalid_argument if newY is NaN (not a number).
 * @throw std::out_of_range if newY is out of bounds.
 */
    void Point::setY(double newY) {
        if (std::isnan(newY)) {
            throw std::invalid_argument("Invalid coordinates: NaN values not allowed.");
        }
        if (std::abs(newY) > DBL_MAX) {
            throw std::out_of_range("Invalid coordinates: Out of bounds.");
        }
        this->coordinate_y=newY;
    }


/**
* @brief Calculates the Euclidean distance between this point and another point.
* @param other The other position.
* @return The distance between this position and the other position.
*/
    double Point::distance(ariel::Point& other) {
        return std::sqrt((this->coordinate_x - other.coordinate_x) + (this->coordinate_y - other.coordinate_y));
    }

/**
* @brief Prints this position to standard output in the format (x, y).
*/
    void Point::print() {
        std::cout<< "["<<this->coordinate_x<<","<< this->coordinate_y<<"]"<<std::endl;
    }

/**
* @brief Overloaded == operator for comparing two positions for equality.
* @param other The other position to compare to.
* @return True if the two positions are equal, false otherwise.
*/
    bool Point::operator==(const Point& other) const {
        return (this->coordinate_x == other.coordinate_x) && (this->coordinate_y == other.coordinate_y);
    }
/**
* @brief Returns a new Position object that is the closest point to the destination point and is at most the given distance from the source point.
* @param source The source position.
* @param dest The destination position.
* @param distance The maximum distance from the source position to the returned position.
* @return The closest point to the destination point that is at most the given distance from the source point.
*/
    Point Point::moveTowards(ariel::Point& source, ariel::Point& dest, double distance) {
        if (distance < 0) {
            throw std::invalid_argument("maxDist cannot be negative");
        }

        if (source == dest) {
            throw std::invalid_argument("source and dest cannot be the same position");
        }
        double dist = source.distance(dest);
        if (dist <= distance) {
            return dest;
        }
        double dx = dest.coordinate_x - source.coordinate_x;
        double dy = dest.coordinate_y - source.coordinate_y;

        double newX = source.coordinate_x + distance * dx/dist;
        double newY = source.coordinate_y + distance * dy/dist;

        return Position(newX,newY);
    }

}