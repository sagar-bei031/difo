add_executable(difo
    main.cpp
    myColors.cpp
    myTree.cpp
    myLinkedList.cpp
    myQueue.cpp
    mySize.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})