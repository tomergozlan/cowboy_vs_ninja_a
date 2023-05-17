//
// Created by Tomer Gozlan on 16/05/2023.
//

#ifndef COWBOY_VS_NINJA_A_TEAM_HPP
#define COWBOY_VS_NINJA_A_TEAM_HPP

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

        void setLeader(Character *newLeader);

        const vector<Character*>& getFighters() const;

        ~Team();

        void add(Character *fighter);

        Character* findClosestCharacter(const Point& location, const std::vector<Character*>& fighters) const;

        void attack(Team *enemyTeam);

        int stillAlive() const;

        void print() const;

    };

}

#endif //COWBOY_VS_NINJA_A_TEAM_HPP
