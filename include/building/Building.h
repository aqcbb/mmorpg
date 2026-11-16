#pragma once
#include <string>

class Building {
protected:
    int id_;
    std::string type_;
    int health_;
    int maxHealth_;
    int x_, y_;
    int buildProgress_;
    char symbol_;

public:
    Building(int id, std::string type, int hp, char sym, int x, int y);
    virtual ~Building() = default;

    virtual void update();
    virtual void produce();

    int getId() const { return id_; }
    std::string getType() const { return type_; }
    int getHealth() const { return health_; }
    int getX() const { return x_; }
    int getY() const { return y_; }
    int getBuildProgress() const { return buildProgress_; }
    bool isCompleted() const { return buildProgress_ >= 100; }
    char getSymbol() const { return symbol_; }
};