/**
 * @file character.cpp
 * @brief Implements the Character class and its derived classes.
 * @author Tomer Gozlan
 * @date 15/05/2023
 */

#include "Character.hpp"

namespace ariel {

/**
 * @brief Constructs a Character object with the specified name and location.
 * @param name The name of the character.
 * @param location The location of the character.
 * @throw std::invalid_argument if the name is empty or if the location coordinates are negative.
 */
    Character::Character(const std::string& name, const ariel::Point& location, const int &hitPoints):
            location(location) ,hitPoints(hitPoints) , name(name), teamMember(false){
        if (name.empty()) {
            throw std::invalid_argument("Error: Name cannot be empty.");
        }
        if (this->location.getX() < 0.0 || this->location.getY() < 0.0) {
            throw std::invalid_argument("Error: Location coordinates cannot be negative.");
        }
        if (hitPoints < 0.0 || hitPoints > 150.0) {
            throw std::out_of_range("Error: hitPoints out of bounds.");
        }
        this->location = location;
        this->hitPoints = hitPoints;
        this->name = name;
        this->teamMember= false;
    }

/**
 * @brief Setter for the HitPoints field.
 * @param NewHitPoints - new value to set the field.
 * @throws std::invalid_argument if the provided hit points value is negative.
 */
    void Character::setHitPoints(int NewHitPoints) {
        if(NewHitPoints < 0){
            throw std::invalid_argument("Error: Hit points must be a non-negative value.");
        }
        if(NewHitPoints > 150){
            throw std::out_of_range("Error:hitPoints out of bounds.");
        }
        this->hitPoints = NewHitPoints;
    }

/**
 * @brief Checks if the character is alive.
 * @return True if the character has more than 0 hit points, indicating they are alive. False otherwise.
 */
    bool Character::isAlive() const {
        return (this->hitPoints > 0);
    }

/**
 * @brief Calculates the Euclidean distance between the current character and another character.
 * @param other A pointer to the other character.
 * @return The Euclidean distance between the current character and the other character.
 * @throw std::invalid_argument If the pointer to the other character is nullptr.
 */
    double Character::distance(const ariel::Character *other) const {
        if (!other) {
            throw std::invalid_argument("Error: Invalid pointer to character.");
        }
        return std::sqrt(std::pow((this->location.getX() - other->location.getX()),2) + std::pow((this->location.getY() - other->location.getY()),2));
    }

/**
 * @brief reduces damage to the character by subtracting the specified amount from its hit points.
 * @param amount The amount of damage to be inflicted.
 */
    void Character::hit(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Error: amount must be non-negative.");
        }

        this->hitPoints -= amount;

        if (this->hitPoints < 0) {
            this->hitPoints = 0;
        }
    }

/**
 * @brief Getter to the name field.
 * @return The name of the character.
 */
    std::string Character::getName() const {
        return this->name;
    }

/**
 * @brief Getter to the location field.
 * @return The location of the character.
 */
    Point Character::getLocation() const {
        return this->location;
    }

    int Character::getHitPoints() const {
        return this->hitPoints;
    }

    bool Character::isTeamMember() const {
        return this->teamMember;
    }

    void Character::setTeamMember(bool newTeamMember) {
        this->teamMember = newTeamMember;
    }
    std::string Character::print() const {
        std::string characterInfo = "name: "+name + ", HitPoints: "+ std::to_string(hitPoints)  + ", location: ";
        characterInfo += location.print();
        return characterInfo;
    }
/**
 * @brief Setter for the location of the character.
 * @param newLocation The new location to set
 * @throw std::out_of_range if the new location is out of bounds
 */
    void Character::setLocation(Point newLocation) {
        if (std::abs(newLocation.getX()) > DBL_MAX || std::abs(newLocation.getY()) > DBL_MAX) {
            throw std::out_of_range("Error: Invalid coordinates. Out of bounds.");
        }
        this->location = newLocation;
    }

/// Cowboy class - defines the Cowboys class, derived from the Character class.

/**
* @brief Constructor for the Cowboy class.
* @param name The name of the cowboy.
* @param location The location of the cowboy on the game board.
* @throws std::invalid_argument if the name is empty.
* @throw std::out_of_range if the hit points over 110 or less then 0.
*/
    Cowboy::Cowboy(const std::string& name, const ariel::Point& location) : Character(name, location, 110) {
        if (name.empty()) {
            throw std::invalid_argument("Error: Name cannot be empty.");
        }
        if (this->getHitPoints() < 0 || this->getHitPoints() > 110) {
            throw std::out_of_range("Error: hitPoints of Cowboy out of bounds.");
        }
        this->bullets = 6;
    }

/**
 * @brief Shoots the enemy character, causing damage and consuming a bullet.
 * @param enemy A pointer to the enemy character to shoot.
 * @throw std::invalid_argument If the enemy pointer is nullptr.
 * @throw std::runtimer_error If cowboy try shoot himself.
 * @throw std::out_of_range If the cowboy is out of bullets.
 * @throw std::runtime_error If the enemy is already dead.
 */
    void Cowboy:: shoot(Character *other){
        if(other==nullptr)
            throw std::invalid_argument ("error: enemey can't be null");
        if(this == other)
            throw std::runtime_error ("error: can't shoot myself");
        if(!(this->isAlive()) || !(other->isAlive()))
            throw std::runtime_error ("error: me or enemy - already dead");
        if(this->hasBullets()){
            this->bullets--;
            other->hit(10);
        }
    }

    /**
    * @brief Checks if the cowboy has bullets left.
    * @return True if the cowboy has bullets, false otherwise.
    */
    bool Cowboy::hasBullets() const {
        return (this->bullets>0);
    }

/**
 * @brief Reloads the cowboy's gun with six new bullets.
 * @throw std::runtimer_error If the cowboy is not alive and try to reload.
 */
    void Cowboy::reload() {
        if (!(this->isAlive())) {
            throw std::runtime_error("Error: Cowboy is not alive. Cannot reload.");
        }
        this->bullets = 6;
    }

    int Cowboy::getBullets() const {
        return this->bullets;
    }

/**
 * @brief Prints the information about the cowboy.
 * This function prints the name, hit points, and location of the cowboy.
 * @note If the cowboy is dead, the hit points and location will not be printed.
 */
    std::string Cowboy::print() const {
        return "C, " + Character::print();
    }
/// Ninja class - defines the Ninja class, derived from the Character class.

/**
 * @brief Constructor for the Ninja class.
 * @param name The name of the ninja.
 * @param location The initial location of the ninja.
 * @param speed The speed of the ninja.
 * @param hitPoints The hit points of the ninja.
 */
    Ninja::Ninja(const std::string& name, const Point& location, int speed , int hitPoints) : Character(name, location,hitPoints) , speed(speed) {
        if (speed < 0) {
            throw std::invalid_argument("Error: Speed cannot be negative.");
        }
        if (hitPoints < 0) {
            throw std::invalid_argument("Error: Hit points cannot be negative.");
        }
        this->speed = speed;
    }
/**
 * @brief Moves the Ninja towards the enemy by a distance equal to its speed.
 * @param enemy A pointer to the enemy Character.
 * @throws std::invalid_argument If the enemy pointer is invalid or the distance is invalid.
 */

    void Ninja::move(ariel::Character *enemy) {
        if (!enemy) {
            throw std::invalid_argument("Error: Invalid pointer to enemy character.");
        }
        if (!isAlive()) {
            return;
        }
        double distance = getLocation().distance(enemy->getLocation());
        if (distance <= 0) {
            throw std::invalid_argument("Error: Invalid distance to enemy.");
        }
        double movement = this->speed;
        if (movement > distance) {
            movement = distance;
        }
        Point newLocation = Point::moveTowards(getLocation(), enemy->getLocation(), movement);
        setLocation(newLocation);
    }
/**
 * @brief Performs a slash attack on the enemy character.
 * @param enemy A pointer to the enemy character.
 * @throws std::invalid_argument if the enemy pointer is invalid.
 * @throws std::runtime_error if the ninja is already dead or the ninja try to slash himself.
 */
    void Ninja::slash(ariel::Character *enemy) {
        if (!enemy) {
            throw std::invalid_argument("Error: Invalid pointer to enemy character.");
        }
        if(this==enemy){
            throw std::runtime_error("Error: Ninja can't slash himself.");
        }
        if (!isAlive() || !(enemy->isAlive())) {
            throw std::runtime_error("Error: Ninja is already dead.");
        }
        double distance = getLocation().distance(enemy->getLocation());
        if (distance < 1) {
            enemy->hit(40);
        }
    }

    std::string Ninja::print() const {
        return " N, " + Character::print();
    }

}