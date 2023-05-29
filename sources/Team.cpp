/**
 * @file Team.cpp
 * @brief Represents a group of fighters, consisting of ninjas and warriors.
 * This class is a group of up to ten fighters, where a fighter can be a ninja or a warrior.
 * Each group is assigned a leader who is one of the fighters. When a group is created, it gets a leader pointer.
 * @author Tomer Gozlan
 * @date 16/05/2023
 */

#include "Team.hpp"

namespace ariel {

/**
 * @brief Constructs a team with the specified leader.
 * @param leader Pointer to the leader of the team.
 * @throws std::invalid_argument If the leader pointer is invalid or the team already has ten fighters.
 * @throws std::runtimer_error If the leader is already member in other team.
 */
    Team::Team(Character *leader) {
        if (!leader) {
            throw std::invalid_argument("Error: Invalid pointer to team leader.");
        }
        if (leader->isTeamMember()) {
            throw std::runtime_error("Error: The leader is already in team.");
        }
        if (this->fighters.size() >= 10) {
            throw std::invalid_argument("Error: The team cannot have more than ten fighters.");
        }
        fighters.push_back(leader);
        this->leader = leader;
        this->leader->setTeamMember(true);
    }

/**
* @brief Get the leader of the team.
* @return Pointer to the leader character.
*/
    Character *Team::getLeader() const {
        return this->leader;
    }

    /**
 * @brief Get the fighters in the team.
 * @return A reference to the vector of fighters in the team.
 */
    const std::vector<Character *> &Team::getFighters() const {
        return fighters;
    }

/**
 * @brief Adds a fighter to the team.
 * @param fighter Pointer to the fighter to be added.
 * @throws std::invalid_argument If the fighter pointer is invalid or the team already has ten fighters.
 */
    void Team::add(Character *fighter) {
        if (!fighter) {
            throw std::invalid_argument("Error: Invalid pointer to team fighter.");
        }
        if (fighter->isTeamMember()) {
            throw std::runtime_error("Error: The character is already in some team.");
        }
        if (this->fighters.size() >= 10) {
            throw std::invalid_argument("Error: The team cannot have more than ten fighters.");
        }
        this->fighters.push_back(fighter);
        fighter->setTeamMember(true);
    }

/**
* @brief Finds the new leader for the team based on the closest living character to a given location.
* @param location The location used to calculate the distances.
* @param fighters A vector containing pointers to the fighters in the team.
*/
    Character *
    Team::findClosestCharacter(const ariel::Point &location, const std::vector<Character *> &fighters) const {
        Character *closestCharacter = nullptr;
        double closestDistance = std::numeric_limits<double>::max();
        for (Character *character: fighters) {
            if (character->isAlive()) {
                double distance = location.distance(character->getLocation());
                if (distance < closestDistance) {
                    closestCharacter = character;
                    closestDistance = distance;
                }
            }
        }
        return closestCharacter;
    }

/**
 * @brief Attacks the enemy team and handles various scenarios, including leader replacement and victim selection.
 * @param enemyTeam Pointer to the enemy team.
 * @throws std::invalid_argument If the enemyTeam pointer is invalid.
 * @throw std::invalid_argument If the ninja type dont fit to the three type: Young,Trained,Old Ninja.
 */
    void Team::attack(ariel::Team *enemyTeam) {
        if (!enemyTeam) {
            throw std::invalid_argument("Error: Invalid pointer to enemy team.");
        }
        if (this == enemyTeam) {
            throw std::runtime_error("Error: Team must attack the enemy team not herself.");
        }
        if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
            throw std::runtime_error("Error: One of the teams was completely eliminated.");
        }
        if (!(this->leader->isAlive())) {
            Point leaderLocation = this->leader->getLocation();
            Character *newLeader = findClosestCharacter(leaderLocation, this->getFighters());
            this->leader = newLeader;
        }
        Character *victim = findClosestCharacter(this->leader->getLocation(), enemyTeam->getFighters());

        for (Character *attacker: fighters) {
            if (attacker->isAlive() && victim->isAlive()) {
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker)) {
                    if (cowboy->hasBullets()) {
                        cowboy->shoot(victim);
                    } else {
                        cowboy->reload();
                    }
                }
            }
            if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
                return;
            }
            if (!victim->isAlive()) {
                victim = findClosestCharacter(leader->getLocation(), enemyTeam->getFighters());
            }
            if (!enemyTeam->leader->isAlive()) {
                Point enemyLeaderLocation = enemyTeam->leader->getLocation();
                Character *enemyNewLeader;
                enemyNewLeader = findClosestCharacter(enemyLeaderLocation, this->getFighters());
                enemyTeam->leader = enemyNewLeader;
            }
        }
        for (Character *attacker: fighters) {
            if (attacker->isAlive() && victim->isAlive()) {
                if (Ninja *ninja = dynamic_cast<Ninja *>(attacker)) {
                    double distance = ninja->getLocation().distance(victim->getLocation());
                    if (distance < 1) {
                        ninja->slash(victim);
                    } else {
                        ninja->move(victim);
                    }
                }
            }
            if (this->stillAlive() == 0 || enemyTeam->stillAlive() == 0) {
                return;
            }
            if (!victim->isAlive()) {
                victim = findClosestCharacter(leader->getLocation(), enemyTeam->getFighters());
            }
            if (!enemyTeam->leader->isAlive()) {
                Point enemyLeaderLocation = enemyTeam->leader->getLocation();
                Character *enemyNewLeader;
                enemyNewLeader = findClosestCharacter(enemyLeaderLocation, this->getFighters());
                enemyTeam->leader = enemyNewLeader;
            }
        }
    }


/**
* @brief Checks the number of alive members in the team.
* @return The number of members in the team that are still alive.
*/
    int Team::stillAlive() const {
        int counter = 0;
        for (Character *fighter: this->fighters) {
            if (fighter->isAlive()) {
                counter++;
            }
        }
        return counter;
    }

/**
* @brief Prints the details of all the fighters in the team.
* Prints the details, such as the name, hit points, and location, of all the fighters in the team.
*/
    void Team::print() const {
        std::cout<<"---------------------"<<std::endl;
        std::cout<<"Team "<<this->leader->getName()<<std::endl;
        std::cout<<"---------------------"<<std::endl;
        std::cout << "Team Status: " << (stillAlive() ? "Alive" : "Defeated") << std::endl;
        std::cout << "Number of Team members: " << (stillAlive() ? std::to_string(stillAlive()) : "0") << std::endl;
        std::cout << "Team Members:" << std::endl;

        for (Character *member: this->fighters) {
            if (member->isAlive()) {
                if (Cowboy *cowboy = dynamic_cast<Cowboy *>(member)) {
                    std::cout  << cowboy->print() << std::endl;
                }
            }
        }
        for (Character *member: this->fighters) {
            if (member->isAlive()) {
                if (Ninja *ninja = dynamic_cast<Ninja *>(member)) {
                    std::cout << ninja->print() << std::endl;
                }
            }
        }
    }

/**
* @brief Destructor for the Team class.
* Frees the memory allocated to all the members (fighters) of the team.
*/
    Team::~Team() {
        for (Character *fighter: fighters) {
            delete fighter;
        }
    }
}
