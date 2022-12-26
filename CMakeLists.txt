cmake_minimum_required(VERSION 3.17)
project(TAL_TO_Groep)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EXISTS /Users/cedricleclercq)
    set(Qt5_DIR /Users/cedricleclercq/Other/Qt/5.15.2/clang_64/lib/cmake/Qt5)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(GLOBAL_SOURCES
        src/Audio.cpp src/Audio.h
        src/AudioRepresentation.cpp src/AudioRepresentation.h
        src/Util.h src/Util.cpp
        # BoyerMooreAutomaton
        src/BoyerMooreAutomaton/BoyerMooreAutomaton.cpp src/BoyerMooreAutomaton/BoyerMooreAutomaton.h
        src/BoyerMooreAutomaton/State.cpp src/BoyerMooreAutomaton/State.h
        # Library
        src/Library/AudioFile.h
        src/Library/Timer.h)

set(UI_SOURCES
        src/UI/CommandManager.cpp src/UI/CommandManager.h
        src/UI/CommandHandler.h
        src/UI/LibraryCmd.cpp src/UI/LibraryCmd.h
        src/UI/RunCmd.cpp src/UI/RunCmd.h
        src/UI/SearchCmd.cpp src/UI/SearchCmd.h
        src/UI/TestRunCmd.cpp src/UI/TestRunCmd.h
        src/UI/ParseCmd.cpp src/UI/ParseCmd.h)

set(GUI_SOURCES
        src/GUI/mainwindow.cpp src/GUI/mainwindow.h
        src/GUI/about.cpp src/GUI/about.h
        src/GUI/AddSongToLibrary.cpp src/GUI/AddSongToLibrary.h
        src/GUI/helppage.cpp src/GUI/helppage.h
        src/GUI/musiclibrary.cpp src/GUI/musiclibrary.h
        src/GUI/songsearcherwindow.cpp src/GUI/songsearcherwindow.h
        src/GUI/GuiManager.cpp src/GUI/GuiManager.h
        src/GUI/foundsongswindow.cpp src/GUI/foundsongswindow.h)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "-O3 -pthread")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_executable(TAL_TO_Groep-Terminal
        src/main.cpp
        ${GLOBAL_SOURCES}
        ${UI_SOURCES})

add_executable(TAL_TO_Groep-Gui
        src/GUI/main.cpp
        ${GLOBAL_SOURCES}
        ${GUI_SOURCES})

target_link_libraries(TAL_TO_Groep-Gui Qt5::Widgets)
