//
// Created by Tomer Gozlan on 17/05/2023.
//
#include "doctest.h"
#include "sources/Character.hpp"
#include "sources/Point.hpp"
#include "sources/Team.hpp"
#include <bits/stdc++.h>

using namespace std;
using namespace ariel;
///@test Point.hpp
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
    CHECK(distance == 5.0);
}

TEST_CASE("Test Case 4: Moving towards a destination point") {
    Point source(2.0, 3.0);
    Point dest(5.0, 7.0);
    Point correctPoint(2.8, 4.6);
    double distance = 2.0;
    Point newPoint = source.moveTowards(source, dest, distance);
    CHECK(newPoint.getX() == newPoint.getX());
    CHECK(newPoint.getY() == newPoint.getY());
}

///@test Team.hpp
TEST_CASE("Test Case 5: Adding a fighter to the team") {
    // Create a team with a leader
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("Tomer", leaderLocation);
    Team team_A(leader);

    // Add a fighter to the team
    Point fighterLocation(3.0, 4.0);
    Character *fighter = new Ninja("Mike", fighterLocation, 100, 10);
    team_A.add(fighter);

    // Check that the fighter was added to the team
    const std::vector<Character *> &fighters = team_A.getFighters();
    CHECK(fighters.size() == 2);
    CHECK(fighters[0]->getName() == "Tomer");
    CHECK(fighters[0]->getLocation().getX() == 1.0);
    CHECK(fighters[0]->getLocation().getY() == 2.0);
    CHECK(fighters[1]->getName() == "Mike");
    CHECK(fighters[1]->getLocation().getX() == 3.0);
    CHECK(fighters[1]->getLocation().getY() == 4.0);

}

TEST_CASE("Test Case 6: Adding more then the capacity of the team size") {
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("Tomer", leaderLocation);
    Team team_of_ten(leader);
    std::vector<std::string> names = {
            "Alice", "Bob", "Charlie", "David", "Eve",
            "Frank", "Grace", "Henry", "Ivy"
    };
    std::vector<Point> points = {{1.0,  23.0},
                                 {4.5,  10.2},
                                 {12.7, 8.9},
                                 {5.0,  17.3},
                                 {0.0,  0.0},
                                 {9.8,  2.1},
                                 {3.6,  11.4},
                                 {7.2,  6.6},
                                 {8.9,  3.3}};
    for (size_t i = 0; i < names.size(); i++) {
        Character *fighter = new Ninja(names[i], points[i], 100, 10);
        team_of_ten.add(fighter);
    }
    CHECK(team_of_ten.stillAlive() == 10);

    //add one more fighter to check if throw exception
    Point location(100.123, 321.100);
    Character *fighter_number11 = new Ninja("throw", location, 100, 10);
    CHECK_THROWS(team_of_ten.add(fighter_number11));
    }

TEST_CASE("Test Case 7: testing findClosestCharacter method") {
    // Create a team with a leader
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("Leader", leaderLocation);
    Team team(leader);

    // Create three very close fighters in different team
    Point fighter1Location(1.0, 2.0205);
    Character *fighter1 = new Ninja("Fighter1", fighter1Location, 100, 10);
    Team team_b(fighter1);

    Point fighter2Location(1.0, 2.02);
    Character *fighter2 = new Ninja("Fighter2", fighter2Location, 100, 10);
    team_b.add(fighter2);

    Point fighter3Location(1.0, 2.025);
    Character *fighter3 = new Ninja("Fighter3", fighter3Location, 100, 10);
    team_b.add(fighter3);

    // Find the closest character to the leader
    Character *closestCharacter = team.findClosestCharacter(leaderLocation, team_b.getFighters());

    // Check that the closest character is the correct one
    CHECK(closestCharacter == fighter2);

}

TEST_CASE("Test Case 8: testing attack method") {
    // Create a team and enemy team
    Point leaderLocation(1.0, 2.0);
    Character *leader = new Cowboy("Leader", leaderLocation);
    Team team(leader);

    Point enemyLeaderLocation(3.0, 4.0);
    Character *enemyLeader = new Cowboy("EnemyLeader", enemyLeaderLocation);
    Team enemyTeam(enemyLeader);

    // Create fighters for both teams
    Point fighter1Location(2.0, 2.5);
    Character *fighter1 = new OldNinja("Fighter1", fighter1Location);
    team.add(fighter1);

    Point fighter2Location(1.5, 1.8);
    Character *fighter2 = new Cowboy("Fighter2", fighter2Location);
    team.add(fighter2);

    Point enemyFighter1Location(2.5, 4.2);
    Character *enemyFighter1 = new YoungNinja("EnemyFighter1", enemyFighter1Location);
    enemyTeam.add(enemyFighter1);

    Point enemyFighter2Location(3.3, 4.5);
    Character *enemyFighter2 = new Cowboy("EnemyFighter2", enemyFighter2Location);
    enemyTeam.add(enemyFighter2);

    team.attack(&enemyTeam);

    CHECK(enemyLeader->isAlive() == true);
    CHECK(enemyFighter1->isAlive() == true);
    CHECK(enemyFighter1->getHitPoints() == 80); // YoungNinja hitPoints : 100 , 2 bullets from cowboys 10 each
    CHECK(enemyFighter2->isAlive() == true);
    CHECK(fighter1->isAlive() == true);
    CHECK(fighter2->isAlive() == true);

    CHECK(fighter1->getHitPoints() == 150);
    if (Cowboy *cowboy = dynamic_cast<Cowboy *>(fighter2)) {
        CHECK(cowboy->getBullets() == 5);
    }

    //Create loop until one of the members die
    for (int i = 0; i < 2; i++) {
        team.attack(&enemyTeam);
    }
    CHECK(enemyLeader->isAlive() == true);
    CHECK(enemyFighter1->isAlive() == false);
    CHECK(enemyFighter1->getHitPoints() ==
          0);//YoungNinja hitPoints : 80 , 4 bullets from cowboys 10 each and 2 slash 40
    CHECK(enemyTeam.stillAlive() == 2);
    CHECK(enemyFighter2->isAlive() == true);
    CHECK(fighter1->isAlive() == true);
    CHECK(fighter2->isAlive() == true);
}

/// @test Character.hpp

TEST_CASE("Test Case 9: testing Character class") {
    // Create a derived class instance to test the common functionalities
    Point Location(2.0, 3.0);
    Character *cowboy = new Cowboy("Tomer", Location);

    // Test isAlive() function
    CHECK(cowboy->isAlive() == true);

    // Test distance() function
    Point otherLocation(5.0, 7.0);
    Character *otherCowboy = new Cowboy("Gozlan", otherLocation);
    CHECK(cowboy->distance(otherCowboy) == 5);

    // Test hit() function
    int hitPoints = cowboy->getHitPoints();
    int damageAmount = 30;
    cowboy->hit(damageAmount);
    CHECK(cowboy->getHitPoints() == (hitPoints - damageAmount));

    // Test setHitPoints() function with valid hitPoints
    int newHitPoints = 80;
    CHECK_NOTHROW(cowboy->setHitPoints(newHitPoints));
    CHECK(cowboy->getHitPoints() == newHitPoints);

    // Test setHitPoints() function with negative hitPoints
    int negativeHitPoints = -50;
    CHECK_THROWS(cowboy->setHitPoints(negativeHitPoints));

    // Test getName() function
    CHECK(cowboy->getName() == "Tomer");

    // Test isTeamMember() function
    CHECK(cowboy->isTeamMember() == false);

    // Test setTeamMember() function
    cowboy->setTeamMember(true);
    CHECK(cowboy->isTeamMember() == true);

}

/// @test Cowboy.hpp

TEST_CASE("Test Case 10: testing Cowboy contractor and method") {
    Point p1(2.0, 3.0);
    Character *cowboy1 = new Cowboy("Tomer", p1);
    Cowboy *cowboy = dynamic_cast<Cowboy *>(cowboy1);
    // Test isAlive() function
    CHECK(cowboy->isAlive() == true);

    // Test hasBullets() function
    CHECK(cowboy->hasBullets() == true);

    // Test getBullets() function
    CHECK(cowboy->getBullets() == 6);

    // Test reload() function
    CHECK_NOTHROW(cowboy->reload());
    CHECK(cowboy->getBullets() == 6);

    // Test shoot() function with valid enemy
    Point p2(4.0, 5.0);
    Character *cowboy2 = new Cowboy("Gozlan", p2);
    Cowboy *otherCowboy = dynamic_cast<Cowboy *>(cowboy2);
    CHECK_NOTHROW(cowboy->shoot(otherCowboy));
    CHECK(otherCowboy->getHitPoints() == 100); // Enemy should be hit with 10 damage

    // Test shoot() function with nullptr enemy
    CHECK_THROWS(cowboy->shoot(nullptr));

    // Test shoot() function shooting itself
    CHECK_THROWS(cowboy->shoot(cowboy));

    // Test shoot() function when cowboy or enemy is already dead
    otherCowboy->hit(110);
    CHECK_THROWS(cowboy->shoot(otherCowboy));
    CHECK_THROWS(otherCowboy->shoot(cowboy));

}

TEST_CASE("Test Case 11: testing Cowboy Reload and Shoot") {
    Point cowboyLocation(2.0, 3.0);
    Cowboy *cowboy = new Cowboy("Tomer", cowboyLocation);

    Point enemyLocation(4.0, 5.0);
    Cowboy *enemy = new Cowboy("Enemy", enemyLocation);

    for (int i = 0; i < 6; i++) {
        cowboy->shoot(enemy);
        CHECK(enemy->getHitPoints() == 110 - (i + 1) * 10);
    }
    CHECK_FALSE(cowboy->hasBullets());
    cowboy->reload();
    CHECK(cowboy->hasBullets());

}
///@test Ninja.hpp

TEST_CASE("Test Case 12: Ninja Move and Slash") {
    Point ninjaLocation(2.0, 3.0);
    OldNinja *ninja1 = new OldNinja("Tomer", ninjaLocation);
    YoungNinja *ninja2 = new YoungNinja("Gozlan", ninjaLocation);

    // Move the ninja to a new location
    Point newLocation(3.0, 4.0);
    ninja2->setLocation(newLocation);
    ninja1->move(ninja2);
    CHECK(ninja1->getLocation().getX() == newLocation.getX());
    CHECK(ninja1->getLocation().getY() == newLocation.getY());
    ninja1->slash(ninja2);
    CHECK(ninja2->getHitPoints() == 60); // 100-40

}







