set(icl "../include/")
set(pgm "programs/")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        ${pgm}logichandler.h
        logichandler.c

        main.c
)
