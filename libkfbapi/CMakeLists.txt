# project(libkfbapi)
#
# include_directories(
#   ${CMAKE_SOURCE_DIR}
#   ${CMAKE_BINARY_DIR}
#   ${Boost_INCLUDE_DIR}
# )

set(kfbapi_SRCS
  alleventslistjob.cpp
  allnoteslistjob.cpp
  allpostslistjob.cpp
  appinfo.cpp
#   authenticationdialog.cpp
#   commentinfo.cpp
  eventinfo.cpp
  eventjob.cpp
  eventslistjob.cpp
  facebookjobs.cpp
#   friendjob.cpp
#   friendlistjob.cpp
#   getcommentsjob.cpp
  likesjob.cpp
  likeinfo.cpp
  listjobbase.cpp
#   noteaddjob.cpp
  noteinfo.cpp
  notejob.cpp
  noteslistjob.cpp
  notificationinfo.cpp
  notificationslistjob.cpp
#   notificationsmarkreadjob.cpp
  pagedlistjob.cpp
#   photojob.cpp
#   postaddjob.cpp
  postinfo.cpp
  postjob.cpp
  postcompositejob.cpp
  postslistjob.cpp
  propertyinfo.cpp
  userinfo.cpp
  userinfojob.cpp

  #connectioninfo.cpp
  #connectionslistjob.cpp
)

add_library(KF5FbAPI SHARED ${kfbapi_SRCS})
generate_export_header(KF5FbAPI BASE_NAME LibKFbAPI EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/libkfbapi_export.h)
add_library(KF5::FbAPI ALIAS KF5FbAPI)

target_include_directories(KF5FbAPI PUBLIC "$<BUILD_INTERFACE:${KFbAPI_BINARY_DIR};${CMAKE_CURRENT_BINARY_DIR}>")
target_include_directories(KF5FbAPI INTERFACE "$<INSTALL_INTERFACE:${KF5_INCLUDE_INSTALL_DIR}/KFbAPI>")

set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})

target_link_libraries(KF5FbAPI PUBLIC Qt5::Core
                                      KF5::CoreAddons
                                      KF5::KIOCore
                                      KF5::I18n
)

set_target_properties(KF5FbAPI PROPERTIES VERSION ${KFBAPI_VERSION_STRING}
                                                   SOVERSION ${KFBAPI_SOVERSION}
                                                   EXPORT_NAME FbAPI
)
install(TARGETS KF5FbAPI EXPORT KF5FbAPITargets ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

install( FILES
  alleventslistjob.h
  allnoteslistjob.h
  allpostslistjob.h
  appinfo.h
#   authenticationdialog.h
#   commentinfo.h
  eventjob.h
  eventinfo.h
  eventslistjob.h
  facebookjobs.h
#   friendlistjob.h
#   friendjob.h
#   getcommentsjob.h
#   getlikesjob.h
#   libkfbapi_export.h
  likeinfo.h
  likesjob.h
  listjobbase.h
  noteinfo.h
  noteslistjob.h
  notejob.h
#   noteaddjob.h
  notificationinfo.h
  notificationslistjob.h
#   notificationsmarkreadjob.h
  pagedlistjob.h
#   photojob.h
  postinfo.h
  postjob.h
#   postaddjob.h
  postslistjob.h
  propertyinfo.h
  userinfojob.h
  userinfo.h
  #connectioninfo.h
  #connectionslistjob.h

  ${CMAKE_CURRENT_BINARY_DIR}/libkfbapi_export.h


 DESTINATION ${KF5_INCLUDE_INSTALL_DIR}/KFbAPI COMPONENT Devel
)
