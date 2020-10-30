set(SOURCES
  # Util
  "util/Assertions.cpp"
  "util/Assertions.h"
)

add_library(ege3d ${SOURCES})
target_link_libraries(ege3d
  X11 GL GLU GLEW
)
install(TARGETS "ege3d" ARCHIVE DESTINATION modules)

