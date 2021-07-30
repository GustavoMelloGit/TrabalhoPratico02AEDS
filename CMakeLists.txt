cmake_minimum_required(VERSION 3.20)
project(TrabalhoPratico02 C)

set(CMAKE_C_STANDARD 11)
set(PROJECT_HEADERS Arvore.h)

add_executable(TrabalhoPratico02 main.c Arvore.c)
