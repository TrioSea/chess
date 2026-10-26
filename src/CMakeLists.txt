set(icl "../include/")
set(pgm "programs/")

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE
        ${icl}mymath.h
        ${icl}calculator.h
        ${icl}calculator.c

        ${pgm}logichandler.h
        logichandler.c

        main.c
)
