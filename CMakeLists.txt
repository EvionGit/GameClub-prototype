cmake_minimum_required(VERSION 3.21)
project(GameClub)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameClub
        src/main.cpp
        include/Base.h src/Base.cpp
        include/Club.h src/Club.cpp
        include/EventDistributor.h src/EventDistributor.cpp
        include/Table.h src/Table.cpp
        include/Analyzers/Analyzer.h src/Analyzers/Analyzer.cpp
        include/Analyzers/ClubAnalyzer.h src/Analyzers/ClubAnalyzer.cpp
        include/Events/OutEventBodyError.h
        include/Events/OutEventBodyUser.h
        include/Events/OutEventBodyUserTable.h
        include/Events/Event.h src/Events/Event.cpp
        include/Events/EventPattern.h src/Events/EventPattern.cpp
        include/Events/IncomingEvent.h src/Events/IncomingEvent.cpp
        include/Events/OutcomingEvent.h src/Events/OutcomingEvent.cpp
        include/Events/InEventBody.h src/Events/InEventBody.cpp
        include/Events/InEventBodyUser.h src/Events/InEventBodyUser.cpp
        include/Events/InEventBodyUserTable.h src/Events/InEventBodyUserTable.cpp
        include/Observer/EventDispatcher.h src/Observer/EventDispatcher.cpp
        include/InputParsers/InputParser.h
        include/InputParsers/FileParser.h src/InputParsers/FileParser.cpp
        include/Subscribers/SubscriberBase.h src/Subscribers/SubscriberBase.cpp
        include/Subscribers/Subscriber.h
)

add_subdirectory(tests)


