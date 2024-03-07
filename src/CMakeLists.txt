add_executable(difo
    main.cpp
    myColors.cpp
    mySize.cpp
    mySort.cpp
    mySlide.cpp
    myTree.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})