#include "LoggingObserver.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
using namespace std;

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify() {
    for (auto observer : observers) {
        observer->update(this);
    }
}

void LogObserver::update(Subject* subject) {
    auto* loggable = dynamic_cast<Iloggable*>(subject);
    if (loggable) {
        writeToLog(loggable->stringToLog());
    }
}

void LogObserver::writeToLog(const string& entry) {
    std::ofstream logFile("gamelog.txt", std::ios::app);
    if (logFile.is_open()) {
        logFile << entry << std::endl;
        logFile.close();
    }
}


//
// Created by amrit on 2023-03-18.
//


