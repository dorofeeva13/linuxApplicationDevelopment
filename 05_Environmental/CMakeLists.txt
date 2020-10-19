cmake_minimum_required (VERSION 3.1)

project (project)

find_library(NCURSES_LIBRARY ncursesw)
find_library(PCRE2_LIBRARY pcre2-8)

set (LIBRARIES
		${NCURSES_LIBRARY}
		${PCRE2_LIBRARY})

option(WITHOUT_UTF "Disable UTF support" OFF)

if(WITHOUT_UTF)
  add_definitions(-DREGEX_USE_UTF=0)
else()
  add_definitions(-DREGEX_USE_UTF=1)
endif()

add_compile_options("-lncurses -ltinfo")
link_libraries("-lncurses -ltinfo")

add_executable (project Window.c)

target_link_libraries(project ${LIBRARIES})