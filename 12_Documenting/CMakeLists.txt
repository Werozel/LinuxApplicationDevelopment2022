cmake_minimum_required(VERSION 3.16)
project(09_I18n C)
set(CMAKE_C_STANDARD 11)

add_executable(main main.c)

add_custom_target(init-translate DEPENDS main
        COMMAND mkdir -p ${CMAKE_SOURCE_DIR}/po/ru
        COMMAND xgettext --keyword=_ --language=C --add-comments ${CMAKE_SOURCE_DIR}/main.c -o ${CMAKE_SOURCE_DIR}/po/main.pot
        COMMAND msginit --input=${CMAKE_SOURCE_DIR}/po/main.pot --locale=ru --charset=UTF-8 --output-file=${CMAKE_SOURCE_DIR}/po/ru/ru.po
        )

add_custom_target(inject-translate DEPENDS main
        COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/ru/LC_MESSAGES/
        COMMAND msgfmt --output-file=${CMAKE_CURRENT_BINARY_DIR}/ru/LC_MESSAGES/main.mo ${CMAKE_SOURCE_DIR}/po/ru/ru.po
        )

add_custom_target(run-ru DEPENDS main translate
        COMMAND LANGUAGE=ru ${CMAKE_CURRENT_BINARY_DIR}/main
        )

add_custom_target(run-en DEPENDS main
        COMMAND LANGUAGE=en ${CMAKE_CURRENT_BINARY_DIR}/main
        )

add_custom_target(clean-git COMMAND git clean -fd ${CMAKE_SOURCE_DIR})
