CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)
PROJECT(QGDSII)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets)

ADD_SUBDIRECTORY(GDS)

ADD_LIBRARY(QGDSII 
	qgdsii.cpp qgdsii.h
	boundaryitem.cpp boundaryitem.h
	pathitem.cpp pathitem.h
	utilities.cpp utilities.h
	)

ADD_EXECUTABLE(testQGDSII main.cpp)

TARGET_LINK_LIBRARIES(QGDSII libGDS)
TARGET_LINK_LIBRARIES(QGDSII Qt5::Widgets)
TARGET_LINK_LIBRARIES(testQGDSII Qt5::Widgets)