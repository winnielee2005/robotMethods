// Header file just declares what everything does, real fucntions go into cpp file
#ifndef ROBOT_H
#define ROBOT_H

#include <string>
#include <vector>

// base class (labelling for organisation)
class Robot {
    protected:
    int x, y; 
    int lives = 3;
    std::string name;
    std::string type;

    public:
    //Constructor to give new robot a name, starting x point, starting y point
    Robot(const std::string name, std::string type, int x, int y); 

    virtual ~Robot()
    {
         // does nothing for now
    }
    
    // nothing here yet, just a rule
    virtual void move() = 0;
    virtual void look() = 0;
    virtual void fire() = 0;
    virtual void think() = 0;
    
    // getter functions for robot name, position x, position y and whether is alive or not
    std::string getName();
    int getX();
    int getY(); 
    bool isAlive();
};

// derived class 1
class SeeingRobot : virtual public Robot {
    public:
    SeeingRobot(std::string name, std::string type, int x, int y);
    virtual void look(int x, int y) override = 0;
};

#endif