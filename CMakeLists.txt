project(kfacebook)

set(KFACEBOOK_VERSION_MAJOR 1)
set(KFACEBOOK_VERSION_MINOR 0)
set(KFACEBOOK_VERSION_RELEASE 0)
set(KFACEBOOK_LIB_VERSION "1.0")
set(KFACEBOOK_LIB_SOVERSION "1")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")
find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${KDE4_ENABLE_EXCEPTIONS}" )

option(KDEPIM_44_COMPAT "Don't crash when using KDEPIM runtime 4.4.x, at the cost of using deprecated KCal API" TRUE)
if(KDEPIM_44_COMPAT)
  add_definitions(-DWANT_DEPRECATED_KCAL_API)
endif(KDEPIM_44_COMPAT)

find_package(KdepimLibs 4.5.63 REQUIRED)

find_program(XSLTPROC_EXECUTABLE xsltproc)
macro_log_feature(XSLTPROC_EXECUTABLE "xsltproc" "The command line XSLT processor from libxslt" "http://xmlsoft.org/XSLT/" TRUE)

set(QJSON_VERSION_REQUIRED 0.7)
find_package(QJSON ${QJSON_VERSION_REQUIRED})
macro_log_feature(QJSON_FOUND "QJSON" "Qt library for handling JSON data" "http://qjson.sourceforge.net/" TRUE "${QJSON_VERSION_REQUIRED}")

configure_file(config.h.cmake "${CMAKE_CURRENT_BINARY_DIR}/config.h")

# pkg-config
if (NOT WIN32)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LibKFacebook.pc.in
                  ${CMAKE_CURRENT_BINARY_DIR}/LibKFacebook.pc
                  @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LibKFacebook.pc
          DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)
endif(NOT WIN32)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/LibKFacebookConfig.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/LibKFacebookConfig.cmake
               @ONLY
)

# this file is used by to check if the installed version can be used.
macro_write_basic_cmake_version_file(${CMAKE_CURRENT_BINARY_DIR}/LibKFacebookConfigVersion.cmake
                                     ${KFACEBOOK_VERSION_MAJOR} ${KFACEBOOK_VERSION_MINOR} ${KFACEBOOK_VERSION_RELEASE})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/LibKFacebookConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/LibKFacebookConfigVersion.cmake
        DESTINATION ${LIB_INSTALL_DIR}/cmake/LibKFacebook)

add_definitions(${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${KDEPIMLIBS_INCLUDE_DIRS}
  ${KDE4_INCLUDES}
  ${QJSON_INCLUDE_DIR}
  ${Boost_INCLUDE_DIR}
)

add_subdirectory(libkfacebook)