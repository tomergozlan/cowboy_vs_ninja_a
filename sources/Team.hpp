//
// Created by Tomer Gozlan on 16/05/2023.
//

#ifndef COWBOY_VS_NINJA_A_TEAM_HPP
#define COWBOY_VS_NINJA_A_TEAM_HPP

#include "Point.hpp"
#include "Character.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

namespace ariel {

    class Team {
    private:
        Character *leader;
        std::vector<Character *> fighters;

    public:
        Team(Character *leader);

        Character* getLeader() const;

        const std::vector<Character*>& getFighters() const;

        ~Team();

        void add(Character *fighter);

        Character* findClosestCharacter(const Point& location, const std::vector<Character*>& fighters) const;

        void attack(Team *enemyTeam);

        int stillAlive() const;

        void print() const;

        // Disable copy constructor
        Team(const Team&) = delete;

        // Disable copy assignment operator
        Team& operator=(const Team&) = delete;

        // Disable move constructor
        Team(Team&&) = delete;

        // Disable move assignment operator
        Team& operator=(Team&&) = delete;


    };

}

#endif //COWBOY_VS_NINJA_A_TEAM_HPP
