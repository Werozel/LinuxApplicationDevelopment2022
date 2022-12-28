cmake_minimum_required(VERSION 3.16)
project(09_I18n C)
set(CMAKE_C_STANDARD 11)

find_package(Doxygen REQUIRED dot)

add_executable(main main.c)

add_custom_target(init-translate DEPENDS main
        COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/po/ru
        COMMAND xgettext --keyword=_ --language=C --add-comments ${CMAKE_SOURCE_DIR}/main.c -o ${CMAKE_SOURCE_DIR}/po/main.pot
        COMMAND msginit --input=${CMAKE_SOURCE_DIR}/po/main.pot --locale=ru --output-file=${CMAKE_SOURCE_DIR}/po/ru/ru.po
        )

add_custom_target(inject-translate DEPENDS main
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/ru/LC_MESSAGES/
        COMMAND msgfmt --output-file=${CMAKE_CURRENT_BINARY_DIR}/ru/LC_MESSAGES/main.mo ${CMAKE_SOURCE_DIR}/po/ru/ru.po
        )

add_custom_target(help-ru DEPENDS main inject-translate
        COMMAND LANGUAGE=ru ${CMAKE_CURRENT_BINARY_DIR}/main --help
        )

add_custom_target(help-en DEPENDS main
        COMMAND LANGUAGE=en ${CMAKE_CURRENT_BINARY_DIR}/main --help
        )

add_custom_target(run-ru DEPENDS main inject-translate
        COMMAND LANGUAGE=ru ${CMAKE_CURRENT_BINARY_DIR}/main
        )

add_custom_target(run-ru-roman DEPENDS main inject-translate
        COMMAND LANGUAGE=ru ${CMAKE_CURRENT_BINARY_DIR}/main -r
        )

add_custom_target(run-en DEPENDS main
        COMMAND LANGUAGE=en ${CMAKE_CURRENT_BINARY_DIR}/main
        )

add_custom_target(run-en-roman DEPENDS main
        COMMAND LANGUAGE=en ${CMAKE_CURRENT_BINARY_DIR}/main -r
        )

add_custom_target(doc
        COMMAND doxygen ${CMAKE_SOURCE_DIR}/Doxyfile.in
        )

add_custom_target(man DEPENDS main inject-translate
        COMMAND help2man --output=${CMAKE_BINARY_DIR}/main.l --name=${CMAKE_BINARY_DIR}/main ${CMAKE_BINARY_DIR}/main
        )

#clean
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/po/main.pot)
