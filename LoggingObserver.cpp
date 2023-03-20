#include "LoggingObserver.h"
#include <algorithm>
using namespace std;


void Subject::attach(Observer *observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify(const ILoggable *source) {
    for (Observer *observer : observers) {
        cout <<"\n\n\n\n\n ***************This section ran" << endl;
        observer->update(source);
    }
}

LogObserver::LogObserver() {
    logFile.open("C:\\Users\\amrit\\CLionProjects\\Assignment2Trial3", std::ios::app);
    cout << "LogObserver created and open log file " << endl;
}

LogObserver::~LogObserver() {
    cout << "LogObserver destrpyed and log file closed" << endl;
    logFile.close();
}

void LogObserver::update(const ILoggable *source) {
    std::cout << "LogObserver::update() called." << std::endl;
    source->stringToLog(logFile);
    logFile << std::endl;
    logFile.flush();
    std::cout << "Log entry written to gamelog.txt." << std::endl;

}

