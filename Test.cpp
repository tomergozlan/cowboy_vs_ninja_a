//
// Created by Tomer Gozlan on 17/05/2023.
//
#include "doctest.h"
#include "sources/Character.hpp"
#include "Team.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace ariel;

TEST_CASE("Test Case 1: Creating a Point object") {
    Point p(2.0, 3.0);
    CHECK(p.getX() == 2.0);
    CHECK(p.getY() == 3.0);
}

TEST_CASE("Test Case 2: Setting new coordinates for a Point object") {
    Point p(2.0, 3.0);
    p.setX(4.0);
    p.setY(5.0);
    CHECK(p.getX() == 4.0);
    CHECK(p.getY() == 5.0);
}

TEST_CASE("Test Case 3: Calculating distance between two points") {
    Point p1(2.0, 3.0);
    Point p2(5.0, 7.0);
    double distance = p1.distance(p2);
    CHECK(distance == doctest::Approx(5.0));
}

TEST_CASE("Test Case 4: Moving towards a destination point") {
    Point source(2.0, 3.0);
    Point dest(5.0, 7.0);
    double distance = 2.0;
    Point newPoint = source.moveTowards(source,dest, distance);
    CHECK(newPoint.getX() == doctest::Approx(2.8));
    CHECK(newPoint.getY() == doctest::Approx(4.6));
}

TEST_CASE("Test Case 5: Check if constructor throws if the argument not valid"){
    double max = DBL_MAX;
    double min = DBL_MIN;
    CHECK_THROWS(Point(max+1.0,5.0));
    CHECK_THROWS(Point(1.0,min-1.0));
}

TEST_CASE("Test Case 6: Check if setter throws if the argument not valid"){
    double max = DBL_MAX;
    double min = DBL_MIN;
    Point p1 (max,10.0);
    Point p2 (10.0,min);
    CHECK_THROWS(p1.setX(max+1.0));
    CHECK_THROWS(p2.setY(min-1.0));
}

TEST_CASE("Test Case 7: Adding a fighter to the team") {
    // Create a team with a leader
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("John", leaderLocation);
    Team team (leader);

    // Add a fighter to the team
    Point fighterLocation(3.0, 4.0);
    Character *fighter = new Ninja("Mike", fighterLocation, 100, 10);
    team.add(fighter);

    // Check that the fighter was added to the team
    const std::vector<Character *> &fighters = team.getFighters();
    CHECK(fighters.size() == 1);
    CHECK(fighters[0]->getName() == "Mike");
    CHECK(fighters[0]->getLocation().getX() == 3.0);
    CHECK(fighters[0]->getLocation().getY() == 4.0);

    // Clean up
    delete fighter;
}

TEST_CASE("Test Case 8: Finding the closest character") {
    // Create a team with a leader
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("John", leaderLocation);
    Team team(leader);

    // Add fighters to the team
    Point fighter1Location(3.0, 4.0);
    Character *fighter1 = new Ninja("Mike", fighter1Location, 100, 10);
    team.add(fighter1);

    Point fighter2Location(5.0, 6.0);
    Character *fighter2 = new Cowboy("Tom", fighter2Location);
    team.add(fighter2);

    // Find the closest character
    const std::vector<Character *> &enemyFighters = team.getFighters(); // Assuming there is an enemy team
    Character *closestCharacter = team.findClosestCharacter(leaderLocation, enemyFighters);

    // Check that the closest character is correct
    CHECK(closestCharacter != nullptr);
    CHECK(closestCharacter->getName() == "Mike");

    // Clean up
    delete fighter1;
    delete fighter2;
}

TEST_CASE("Test Case 8: Attacking an enemy team") {
    // Create a team with a leader
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("John", leaderLocation);
    Team team(leader);

    // Add fighters to the team
    Point fighter1Location(3.0, 4.0);
    Character *fighter1 = new Ninja("Mike", fighter1Location, 100, 10);
    team.add(fighter1);

    Point fighter2Location(5.0, 6.0);
    Character *fighter2 = new Cowboy("Tom", fighter2Location);
    team.add(fighter2);


    // Create an enemy team with NULL pointer
    CHECK_THROWS(Team (nullptr));

    // Create a enemy team with a leader
    Point enemyleaderLocation(2.0, 3.0);
    Character *enemyleader = new Cowboy("John", leaderLocation);
    Team enemyTeam(enemyleader);

    // Add fighters to the enemy team
    Point enemyFighter1Location(10.0, 7.0);
    Character *enemyFighter1 = new Ninja("Mike", enemyFighter1Location, 100, 10);
    team.add(enemyFighter1);

    Point enemyFighter2Location(13.0, 3.0);
    Character *enemyFighter2 = new Cowboy("Tom", enemyFighter2Location);
    team.add(enemyFighter2);

    // Attack the enemy team
    team.attack(&enemyTeam);

    // Attack the enemy team
    team.attack(&enemyTeam);

// Perform assertions to validate the attack logic
    CHECK(team.stillAlive() == 2);  // Check if the team still has 2 members after the attack
    CHECK(enemyTeam.stillAlive() < 2);  // Check if the enemy team has less than 2 members after the attack

// Iterate over the fighters in the enemy team and check their health after the attack
    for (Character* enemyFighter : enemyTeam.getFighters()) {
        CHECK(enemyFighter->getHitPoints() < 100);  // Check if the enemy fighter's health decreased after the attack
    }

// Iterate over the fighters in the team and check their health after the attack
    for (Character* teamFighter : team.getFighters()) {
        CHECK(teamFighter->getHitPoints() == 100);  // Check if the team fighter's health remains the same after the attack
    }

    // Clean up
    delete fighter1;
    delete fighter2;
}


