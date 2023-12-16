option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(PROJECT_SRC "EpicProject.cpp" "EpicProject.h" "Wall64.png")

include_directories( images/ )


add_executable (EpicProject "${PROJECT_SRC}")
target_link_libraries(EpicProject PRIVATE sfml-graphics)
target_compile_features(EpicProject PRIVATE cxx_std_17)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET EpicProject PROPERTY CXX_STANDARD 20)
endif()


