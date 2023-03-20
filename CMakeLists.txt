cmake_minimum_required(VERSION 3.24)
project(Assignment2Trial3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assignment2Trial3 main.cpp PlayerDriver.cpp Player.cpp OrdersDriver.cpp Orders.cpp MapDriver.cpp Map.cpp LoggingObserver.cpp GameEngineDriver.cpp GameEngine.cpp CommandProcessing.cpp CardsDriver.cpp Cards.cpp)
