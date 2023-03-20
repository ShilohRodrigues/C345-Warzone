//
// Created by amrit on 2023-03-18.
//

#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class ILoggable;
class Observer;
class Subject;

class ILoggable {
public:
    virtual void stringToLog(ostream& out) const = 0;
};

class Observer {
public:
    virtual void update(const ILoggable *source) = 0;
};

class Subject {
private:
    std::vector<Observer *> observers;

public:
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notify(const ILoggable *source);
};

class LogObserver : public Observer {
private:
    std::ofstream logFile;

public:
    LogObserver();
    ~LogObserver();
    void update(const ILoggable *source) override;
};


#endif //LOGGINGOBSERVER_H
