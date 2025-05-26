#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Daddy of all robot
class Robot{
protected:
    std::string name;
    std::string type;
    int positionX, positionY;
    int shells = 10;
    int livesLeft = 3;
    int upgradeCount = 0;


public:
    virtual ~Robot() {}

    virtual void performTurn() = 0;
    virtual void look(int dx, int dy) = 0;
    virtual void fire(int dx, int dy) = 0;
    virtual void moving(int dx, int dy) = 0;
    virtual void upgrade(std::string area) = 0;
    virtual void think() = 0;

};

class MovingRobot {
public:
    virtual void moving(int dx, int dy) = 0;
    virtual ~MovingRobot() {}
};

class ShootingRobot {
public:
    virtual void fire(int dx, int dy) = 0;
    virtual ~ShootingRobot() {}
};

class SeeingRobot {
public:
    virtual void look(int dx, int dy) = 0;
    virtual ~SeeingRobot() {}
};

class ThinkingRobot {
public:
    virtual void think() = 0;
    virtual ~ThinkingRobot() {}
};

//Inherit from this long ahh code from above lmao
class GenericRobot : public Robot, public MovingRobot, public ShootingRobot, public SeeingRobot, public ThinkingRobot {
private:
    bool isScout = false;
    int scoutsLeft = 0;

public:
    GenericRobot(std::string robotName, int x, int y){
        name = robotName;
        type = "GenericRobot";
        positionX = x;
        positionY = y;
    }
    
    void performTurn() override{
        think();
        look(0,0);
        moving(1,0);
        fire(1,0);
    }

    void look(int dx, int dy) override {
        if (isScout && scoutsLeft >0){
            cout << name << " uses ScoutBot ability to scan the battlefield. Scouts left: "<< scoutsLeft <<"\n";
            scoutsLeft--;
        } else {
            cout << name << " is looking at (" << positionX + dx <<","<< positionY + dy << ")\n";
        }
}
    void fire(int dx, int dy) override {
        if (dx == 0 && dy == 0) {
            cout << name << " cannot fire at itself!\n";
            return;
        }

        if (shells > 0) {
            shells--;
            cout << name << " fires at (" << positionX + dx << ", " << positionY + dy << "). Shells left: " << shells << "\n";
        } else {
            cout << name << " has no shells left!\n";
        }

        // Declare hit chance
        int chance = rand() % 100;
        bool hit = chance < 70;

        if (hit){
            cout << "Enemy robot is destroyed!\n";
            

            if (upgradeCount < 3) {
                upgrade("Seeing");
            }else{
                cout<<"Shot missed!\n";
            }
        }
    }
    void moving(int dx, int dy) override {
    positionX += dx;
    positionY += dy;
    cout << name << " moved to (" << positionX << ", " << positionY << ")\n";
}
    void upgrade(std::string area) override {
    if (upgradeCount >= 3) {
        cout << name << " cannot upgrade anymore!\n";
        return;
    }

    cout << name << " upgrades in area: " << area << "\n";

    if (area == "Seeing" && !isScout) {
        isScout = true;
        scoutsLeft = 3;
        cout << name << " has gained ScoutBot abilities! \n";
    }
    upgradeCount++;
}
    void think() override {
    cout << name << " is thinking...\n";
}
};


//Battlefield
class Battlefield {
private:
    int width, height;
    vector<vector<char>> grid; //2D

public:
    Battlefield(int w, int h) {
        width = w;
        height = h;
        grid = vector<vector<char>>(h, vector<char>(w, '.'));
    }

    void clear() {
        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                grid[i][j] = '.';
    }

    void placeRobot(int x, int y, char symbol) {
        if (x >= 0 && x < width && y >= 0 && y < height)
            grid[y][x] = symbol;
    }

    void display() {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j)
                cout << grid[i][j] << ' ';
            cout << '\n';
        }
    }
};



int main() {
    GenericRobot gr("Jet", 5, 5);
    Battlefield field(10, 10);

    field.clear();
    field.placeRobot(5, 5, 'G'); // 'G' for GenericRobot
    field.display();

    gr.performTurn();
    return 0;
};


