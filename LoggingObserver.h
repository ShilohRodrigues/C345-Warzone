//
// Created by amrit on 2023-03-18.
//

#ifndef LOGGINGOBSERVER_H
#define LOGGINGOBSERVER_H
#include <string>
#include <vector>
using namespace std;

class Iloggable{
public:
    //abstract class used for our polymorphed classes
    [[nodiscard]] virtual string stringToLog() const = 0;
};

//Forward declaration of class subject so our class observer can use it
class Subject;

class Observer {
public:
    //abstract class used for our polymorphed classes
    virtual void update(Subject* subject) = 0;
};


class Subject {
protected:
    std::vector<Observer*> observers;
public:
    //adding a virtual constructor makes subject polymorphic
    virtual ~Subject() = default;
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();
};

class LogObserver : public Observer {
public:
    void update(Subject* subject) override;
    static void writeToLog(const std::string& entry);
};






#endif //LOGGINGOBSERVER_H
