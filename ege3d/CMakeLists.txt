set(SOURCES
  # Util
  "util/Assertions.cpp"
  "util/Assertions.h"
  "util/Color.cpp"
  "util/Color.h"

  # Window
  "window/Keyboard.cpp"
  "window/Keyboard.h"
  "window/Mouse.cpp"
  "window/Mouse.h"
  "window/SystemEvent.cpp"
  "window/SystemEvent.h"
  "window/Window.cpp"
  "window/Window.h"
  "window/WindowImpl.cpp"
  "window/WindowImpl.h"
  "window/WindowSettings.cpp"
  "window/WindowSettings.h"
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  set(SOURCES
    ${SOURCES}

    # Window
    "window/XWindowImpl.cpp"
    "window/XWindowImpl.h"
  )
endif()

string(ASCII 27 ESC)
message("-- ${ESC}[33mAdding source files...${ESC}[m")

add_library(ege3d ${SOURCES})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  target_link_libraries(ege3d
    PRIVATE X11 GL GLU GLEW
  )
else()
  message(FATAL "Target not supported!")
endif()

target_include_directories(ege3d PUBLIC ${CMAKE_SOURCE_DIR})

install(TARGETS "ege3d" ARCHIVE DESTINATION lib)
# install(TARGETS "ege3d" PUBLIC_HEADER DESTINATION include)

