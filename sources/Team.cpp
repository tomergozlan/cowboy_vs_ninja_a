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
 */
    Team::Team(Character *leader) {
        if (!leader) {
            throw std::invalid_argument("Error: Invalid pointer to team leader.");
        }
        if (this->fighters.size() >= 10) {
            throw std::invalid_argument("Error: The team cannot have more than ten fighters.");
        }
        fighters.push_back(leader);
        this->leader = leader;
    }

/**
* @brief Get the leader of the team.
* @return Pointer to the leader character.
*/
    Character *Team::getLeader() const {
        return this->leader;
    }

/**
 * @brief Set the leader of the team.
 * @param newLeader Pointer to the new leader character.
 * @throws std::invalid_argument If the newLeader pointer is invalid.
 */
    void Team::setLeader(Character *newLeader) {
        if (!newLeader) {
            throw std::invalid_argument("Error: Invalid pointer to new team leader.");
        }
        bool isMember = false;
        for (Character *fighter: this->fighters) {
            if (fighter == newLeader) {
                isMember = true;
                break;
            }
        }
        if (!isMember) {
            throw std::invalid_argument("Error: The new team leader must be a member of the team.");
        }
        this->leader = newLeader;
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
        if (this->fighters.size() >= 10) {
            throw std::invalid_argument("Error: The team cannot have more than ten fighters.");
        }
        this->fighters.push_back(fighter);
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
                double distance = location.ariel::Character::distance(character->getLocation());
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
        if (!(this->leader->isAlive())) {
            Point leaderLocation = this->leader->getLocation();
            Character *newLeader = findClosestCharacter(leaderLocation, this->fighters);
            setLeader(newLeader);
        }
        Character *victim = findClosestCharacter(this->leader->getLocation(), enemyTeam->fighters);
        while (!this->fighters.empty() && !enemyTeam->fighters().empty()) {
            for (Character *attacker: fighters) {
                if (attacker->isAlive()) {
                    Cowboy *cowboy = dynamic_cast<Cowboy *>(attacker);
                    if (cowboy) {
                        if (cowboy->getBullets() > 0) {
                            cowboy->shoot(victim);
                            if (!victim->isAlive()) {
                                victim = findClosestCharacter(leader->getLocation(),
                                                                        enemyTeam->getFighters());
                            }
                        } else {
                            cowboy->loadBullets();
                        }
                    } else {
                        double distance = getLocation().distance(enemy->getLocation());
                        Ninja *ninja = dynamic_cast<Ninja *>(attacker);
                        switch (ninja->getNinjaType()) {
                            case "YoungNinja":
                                if (distance < 1) {
                                    ninja->slash(victim);
                                    if (!victim->isAlive()) {
                                        victim = findClosestCharacter(leader->getLocation(),
                                                                      enemyTeam->getFighters());
                                    }
                                } else {
                                    ninja->move(victim);
                                }
                                break;
                            case "TrainedNinja":
                                if (distance < 1) {
                                    ninja->slash(victim);
                                    if (!victim->isAlive()) {
                                        victim = findClosestCharacter(leader->getLocation(),
                                                                      enemyTeam->getFighters());
                                    }
                                } else {
                                    ninja->move(victim);
                                }
                                break;
                            case "OldNinja":
                                if (distance < 1) {
                                    ninja->slash(victim);
                                    if (!victim->isAlive()) {
                                        victim = findClosestCharacter(leader->getLocation(),
                                                                      enemyTeam->getFighters());
                                    }
                                } else {
                                    ninja->move(victim);
                                }
                                break;

                            default: throw std::invalid_argument("Error: Type of ninja dont fit.")
                        }
                        if (!victim->isAlive()) {
                            victim = findClosestCharacter(leader->getLocation(), enemyTeam->getFighters());
                        }
                    }
                }
            }
        }
    }

/**
* @brief Checks the number of alive members in the team.
* @return The number of members in the team that are still alive.
*/
    int Team::stillAlive() const {
        int counter=0;
        for(Character* fighter : this->fighters){
            if (fighter->isAlive()){
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
        std::cout << "Team Cowboys: " << std::endl;
        for (Character *fighter : fighters) {
            Cowboy *cowboy = dynamic_cast<Cowboy *>(fighter);
            if (cowboy) {
                cowboy->print();
            }
        }

        std::cout << "Team Ninjas: " << std::endl;
        for (Character *fighter : fighters) {
            Ninja *ninja = dynamic_cast<Ninja *>(fighter);
            if (ninja) {
                ninja->print();
            }
        }

        std::cout << "Team Leader: ";
        leader->print();
    }

/**
* @brief Destructor for the Team class.
* Frees the memory allocated to all the members (fighters) of the team.
*/
    Team::~Team() {
        for (Character* fighter : fighters) {
            delete fighter;
        }
    }
}
