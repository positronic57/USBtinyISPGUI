cmake_minimum_required(VERSION 3.1.0)

project(saf LANGUAGES CXX)

# Set software version related variables
set(MAJOR_VERSION 1)
set(MINOR_VERSION 3)
set(RELEASE_VERSION 0)

# Define C++ standard required for Qt5 code
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set variables required for building Qt5 applications
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(pugixml REQUIRED)

# Define the include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add the source files from "src" folder to the build.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SOURCE_FILES)

# Define the list of source files.
set (SOURCE_LIST
${SOURCE_FILES}
resource.qrc
)

add_executable(saf ${SOURCE_LIST})

# Some macros used in code
target_compile_definitions(saf PUBLIC 
	APPLICATION_MAJOR_VERSION=${MAJOR_VERSION}
	APPLICATION_MINOR_VERSION=${MINOR_VERSION}
	APPLICATION_RELEASE_VERSION=${RELEASE_VERSION}
)

# Link the binary against Qt5 libraries, libpugixml and libusb
target_link_libraries(saf Qt5::Widgets pugixml usb)

# Installation steps. They will be executed in the same order as listed/defined.
# Create the target folder for installation
install(DIRECTORY DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})

# Copy the build artifact in the installation folder
install(TARGETS saf
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
)

# Copy the config subfolder with its content
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/config/ DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/config
	FILES_MATCHING PATTERN "*.xml"
)

