#include <iostream>
#include <string>
#include <ctime> 

using namespace std;

class Ball {
private:
    int x, y;

public:
    Ball() : x(0), y(0) {} 

    void move(int dx, int dy) { x += dx; y += dy; }

    pair<int, int> getPosition() const { return make_pair(x, y); } 

    int getX() const { return x; }

    int getY() const { return y; }
};

class Goal {
public:
    static const int goalX = 3;
    static const int goalY = 3;

    bool isGoalReached(int ballX, int ballY) const {
        return ballX == goalX && ballY == goalY;
    }
};

class Robot {
private:
    string name;
    int hits;

public:
    Robot(string n) : name(n), hits(0) {}

    void hitBall(Ball &ball, const string &direction) {
        if (direction == "up") ball.move(0, 1);
        else if (direction == "down") ball.move(0, -1);
        else if (direction == "left") ball.move(-1, 0);
        else if (direction == "right") ball.move(1, 0);
        hits++;
    }

    int getHits() const { return hits; }

    string getName() const { return name; }
};

class Team {
private:
    string teamName;
    Robot *robot;

public:
    Team(string tName, string rName) : teamName(tName) { 
        robot = new Robot(rName); 
    }

    ~Team() { delete robot; }

    Robot* getRobot() const { return robot; }

    string getTeamName() const { return teamName; }
};

class Game {
private:
    Team *teamOne;
    Team *teamTwo;
    Ball ball;
    Goal goal;

public:
    Game(string team1, string robot1, string team2, string robot2) {
        teamOne = new Team(team1, robot1);
        teamTwo = new Team(team2, robot2);
    }
    
    ~Game() {
        delete teamOne;
        delete teamTwo;
    }
    
    void play(Team *team) {
        ball = Ball(); 
        Robot *robot = team->getRobot();
        cout << team->getTeamName() << "'s turn...\n";
    
        while (!goal.isGoalReached(ball.getX(), ball.getY())) {
            int ballX = ball.getX();
            int ballY = ball.getY();
    
            int randomChance = rand() % 10; 
    
            if (randomChance < 2) { 
                string directions[] = {"up", "down", "left", "right"};
                robot->hitBall(ball, directions[rand() % 4]);
            } else {
                if (ballX < Goal::goalX) 
                    robot->hitBall(ball, "right");
                else if (ballX > Goal::goalX) 
                    robot->hitBall(ball, "left");
    
                if (ballY < Goal::goalY) 
                    robot->hitBall(ball, "up");
                else if (ballY > Goal::goalY) 
                    robot->hitBall(ball, "down");
            }
        }
    
        cout << team->getTeamName() << " reached the goal in " << robot->getHits() << " hits!\n";
    }
    
    
    
    void declareWinner() {
        int hitsOne = teamOne->getRobot()->getHits();
        int hitsTwo = teamTwo->getRobot()->getHits();
        cout << "\n--- Game Over! ---\n";
        if (hitsOne < hitsTwo)
            cout << teamOne->getTeamName() << " wins!\n";
        else if (hitsTwo < hitsOne)
            cout << teamTwo->getTeamName() << " wins!\n";
        else
            cout << "It's a tie!\n";
    }
    
    void startGame() {
        play(teamOne);
        play(teamTwo);
        declareWinner();
    }
};

int main() {
    srand(time(0)); 
    Game game("Team Arsalan", "Robot A", "Team Tuheed", "Robot T");
    game.startGame();
    return 0;
}
