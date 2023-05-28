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
    };

    class Cowboy : public Character {
    private:
        int bullets;

    public:
        Cowboy(const std::string& name, const Point& location);

        void shoot(Character* enemy);

        bool hasBullets() const;

        void reload();

        std::string print() const override;
    };

    class Ninja : public Character {
    protected:
        int speed;

    public:
        Ninja(const std::string& name, const Point& location, int speed, int hitPoints);

        void move(Character* enemy);

        void slash(Character* enemy);

        std::string print() const override;

    };

    class YoungNinja : public Ninja {
    public:
        YoungNinja(const std::string& name, const Point& location) : Ninja(std::move(name) , location , 14 ,100){}
    };

    class TrainedNinja : public Ninja {
    public:
        TrainedNinja(const std::string& name, const Point& location): Ninja(std::move(name),location,12,120){}
    };

    class OldNinja : public Ninja {
    public:
        OldNinja(const std::string& name, const Point& location): Ninja(std::move(name),location,8,150){}
    };

}

#endif // COWBOY_VS_NINJA_A_CHARACTER_HPP
