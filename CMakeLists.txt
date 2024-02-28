cmake_minimum_required(VERSION 3.5)

project(memory VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    Include/qtLibrary.h
    Include/cPlusPlusLibrary.h
    Enums/segmentsenum.h
    Server/Ram/Sections/AbstRam/absram.h
    Server/ControlBlock/controlblock.h
    Server/ControlBlock/controlblock.cpp
    Server/Controller/controller.h
    Server/Controller/controller.cpp
    Server/Ram/Sections/AbstRam/absram.cpp
    Server/Ram/RamController/RamController.h
    Server/Ram/RamController/RamController.cpp
    Server/Statements/Scope/scope.h
    Server/Statements/Scope/scope.cpp
    Server/Statements/Function/function.h
    Server/Statements/Function/function.cpp
    Server/Ram/test.h
    Server/Ram/Sections/Stack/stack.h
    Server/Ram/Sections/Stack/stack.cpp
    Server/Ram/Sections/Heap/heap.h
    Server/Ram/Sections/Heap/heap.cpp
    Server/Ram/Sections/Bss/bss.h
    Server/Ram/Sections/Bss/bss.cpp
    Server/Ram/Sections/Data/data.h
    Server/Ram/Sections/Data/data.cpp
    Server/Ram/Sections/ReadOnly/readonly.h
    Server/Ram/Sections/ReadOnly/readonly.cpp
    Server/Ram/Sections/SymTab/SymTab.h
    Server/Ram/Sections/SymTab/SymTab.cpp
    UserInterface/UISources/main.cpp
    UserInterface/UISources/mainwindow.cpp
    UserInterface/UIHeaders/mainwindow.h
    UserInterface/UIHeaders/uiinterface.h
    UserInterface/UISources/uiinterface.cpp
    UserInterface/UIHeaders/ramslot.h
    UserInterface/UISources/ramslot.cpp
    UserInterface/UIHeaders/ramsegment.h
    UserInterface/UISources/ramsegment.cpp
    UserInterface/UIHeaders/styleutils.h
    UserInterface/UISources/styleutils.cpp
)

add_executable(memory ${PROJECT_SOURCES}
    Server/Statements/Function/function.h Server/Statements/Function/function.cpp)

# Specify the precompiled header for the 'memory' target
set(PRECOMPILED_HEADER "${CMAKE_CURRENT_BINARY_DIR}/precompiled.h")
file(WRITE ${PRECOMPILED_HEADER} "// Precompiled header\n")
file(APPEND ${PRECOMPILED_HEADER} "#include \"../memory/Include/qtLibrary.h\"\n")
file(APPEND ${PRECOMPILED_HEADER} "#include \"../memory/Include/cPlusPlusLibrary.h\"\n")

# Specify the precompiled header for the 'memory' target
target_precompile_headers(memory PRIVATE ${PRECOMPILED_HEADER})

# Now, link libraries
target_link_libraries(memory PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


set_target_properties(memory PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS memory BUNDLE DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
