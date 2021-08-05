cmake_minimum_required(VERSION 3.20)
project(TrabalhoPratico02 C)

set(CMAKE_C_STANDARD 11)
set(PROJECT_HEADERS
        src/header/Arvore.h
        )

add_executable(TrabalhoPratico02
        main.c
        src/functions/Arvore.c
        src/functions/Menu.c
        src/functions/Eleitor.c
        )
