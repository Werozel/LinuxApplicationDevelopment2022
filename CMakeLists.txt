cmake_minimum_required(VERSION 3.24)
project(LinuxApplicationDevelopment2022 C)

set(CMAKE_C_STANDARD 11)

include_directories(03_Multifile)

add_executable(LinuxApplicationDevelopment2022
        01_GitBuildReq/main.c
        02_TerminalProject/Show.c
        03_Multifile/const.c
        03_Multifile/fun.c
        03_Multifile/outlib.h
        03_Multifile/prog.c
        05_Debugging/range.c
        06_Regexps/esub.c
        07_TracingFencing/move.c
        07_TracingFencing/remove.c
        08_Environmental/rhasher.c
        12_Documenting/main.c)
