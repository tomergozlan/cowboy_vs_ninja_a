/**
 * @file Character.hpp
 * @brief Defines the Character class and its subclasses Cowboy, Ninja, YoungNinja, TrainedNinja, and OldNinja.
 * @author Tomer Gozlan
 * @date 15/05/2023
 */

#ifndef COWBOY_VS_NINJA_A_CHARACTER_HPP
#define COWBOY_VS_NINJA_A_CHARACTER_HPP

#include <iostream>
#include <string>
#include "Point.hpp"

namespace ariel {

    class Character {

    private:
        Point location;
        int hitPoints;
        string name;
    public:
        Character(const std::string &name, const Point &location , const int &hitPoints );

        void setHitPoints(int NewHitPoints);

        bool isAlive() const;

        double distance(const Character *other) const;

        void hit(int amount);

        std::string getName() const;

        Point getLocation() const;

        int getHitPoints() const;

        void setLocation(Point newLocation);

        virtual void print() const = 0;
    };

    class Cowboy : public Character {
    private:
        int bullets;
    public:
        Cowboy(const std::string &name, const Point &location);

        void shoot(Character *enemy);

        bool hasBullets() const;

        void reload();

        void print() const override;
    };

/**
* @file Ninja.hpp
* @brief Defines the Ninja class, derived from the Character class.
* The Ninja class represents a specific type of character - a ninja.
* @author Tomer Gozlan
* @date 15/05/2023
*/
    class Ninja : public Character {
    protected:
        int speed;
    public:
        Ninja(const std::string &name, const Point &location, int speed, int hitPoints);

        void move(Character *enemy);

        void slash(Character *enemy);
    };

    class YoungNinja : public Ninja {
    public:
        YoungNinja(const std::string &name, const Point &location);
    };

    class TrainedNinja : public Ninja {
    public:
        TrainedNinja(const std::string &name, const Point &location);
    };

    class OldNinja : public Ninja {
    public:
        OldNinja(const std::string &name, const Point &location);
    };

}

#endif //COWBOY_VS_NINJA_A_CHARACTER_HPP