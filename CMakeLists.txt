cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

set(TARGETNAME endecrypt)
project(${TARGETNAME})

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt packages on Mac (change Qt version depending on your system)
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(CMAKE_PREFIX_PATH "~/dev/tools/Qt/6.5.0/macos/lib/cmake")
	find_package(Qt6 REQUIRED COMPONENTS Core Gui widgets)
endif()

# Package setup
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()
find_package(cryptopp CONFIG REQUIRED)

add_subdirectory(src/app)

# CPack
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Basic RSA Encryption/Decryption.")
set(CPACK_PACKAGE_VENDOR "Josh Bailey")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE.md")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
#set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/Utilities/images/InstallIcon.bmp")
#set(CPACK_NSIS_INSTALLED_ICON_NAME "bin/${TARGETNAME}.exe")
set(CPACK_NSIS_DISPLAY_NAME "endecrypt")
set(CPACK_NSIS_HELP_LINK "[INSERT PROJECT WEBSITE]")
set(CPACK_NSIS_URL_INFO_ABOUT "[INSERT PERSONAL WEBSITE]")
set(CPACK_NSIS_CONTACT "joshhhbailey@gmail.com")
#set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_PACKAGE_EXECUTABLES "${TARGETNAME}" "endecrypt")
include(CPack)