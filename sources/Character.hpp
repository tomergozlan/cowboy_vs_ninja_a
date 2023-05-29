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
        std::string name;
        bool teamMember;

    public:
        Character(const std::string& name, const Point& location, const int& hitPoints);

        virtual ~Character() = default;

        void setHitPoints(int NewHitPoints);

        bool isAlive() const;

        double distance(const Character* other) const;

        void hit(int amount);

        std::string getName() const;

        Point getLocation() const;

        int getHitPoints() const;

        bool isTeamMember() const;

        void setTeamMember(bool newTeamMember);

        void setLocation(Point newLocation);

        virtual std::string print() const = 0;

        // Define copy constructor
        Character(const Character& other) = default;

        // Define copy assignment operator
        Character& operator=(const Character& other) = default;

        // Define move constructor
        Character(Character&& other) = default;

        // Define move assignment operator
        Character& operator=(Character&& other) = default;
    };

    class Cowboy : public Character {
    private:
        int bullets;

    public:
        Cowboy(const std::string& name, const Point& location);

        void shoot(Character* enemy);

        bool hasBullets() const;

        void reload();

        int getBullets() const;

        std::string print() const override;
    };

    class Ninja : public Character {
    private:
        int speed;

    public:
        Ninja(const std::string& name, const Point& location, int speed, int hitPoints);

        void move(Character* enemy);

        void slash(Character* enemy);

        std::string print() const override;

    };

    class YoungNinja : public Ninja {
    private:
        static const int YOUNG_NINJA_SPEED=14;
        static const int YOUNG_NINJA_HIT_POINTS=100;

    public:
        YoungNinja(const std::string& name, const Point& location) : Ninja(name , location , YOUNG_NINJA_SPEED ,YOUNG_NINJA_HIT_POINTS){}
    };

    class TrainedNinja : public Ninja {
    private:
        static const int TRAINED_NINJA_SPEED=12;
        static const int TRAINED_NINJA_HIT_POINTS=120;
    public:
        TrainedNinja(const std::string& name, const Point& location): Ninja(name,location,TRAINED_NINJA_SPEED,TRAINED_NINJA_HIT_POINTS){}
    };

    class OldNinja : public Ninja {
    private:
        static const int OLD_NINJA_SPEED=8;
        static const int OLD_NINJA_HIT_POINTS=150;
    public:
        OldNinja(const std::string& name, const Point& location): Ninja(name,location,OLD_NINJA_SPEED,OLD_NINJA_HIT_POINTS){}
    };

}

#endif // COWBOY_VS_NINJA_A_CHARACTER_HPP
