project(libkfbapi)

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_BINARY_DIR}
  ${Boost_INCLUDE_DIR}
)

set(kfbapi_SRCS
  allpostslistjob.cpp
  authenticationdialog.cpp
  userinfojob.cpp
  userinfo.cpp
  friendlistjob.cpp
  friendjob.cpp
  photojob.cpp
  eventslistjob.cpp
  eventinfo.cpp
  util.cpp
  alleventslistjob.cpp
  eventjob.cpp
  noteinfo.cpp
  noteslistjob.cpp
  allnoteslistjob.cpp
  notejob.cpp
  noteaddjob.cpp
  facebookjobs.cpp
  pagedlistjob.cpp
  listjobbase.cpp
  postinfo.cpp
  postjob.cpp
  postaddjob.cpp
  postslistjob.cpp
  propertyinfo.cpp
  appinfo.cpp
  commentinfo.cpp
  likeinfo.cpp
  notificationinfo.cpp
  notificationslistjob.cpp
  getlikesjob.cpp
  getcommentsjob.cpp
  notificationsmarkreadjob.cpp
  #connectioninfo.cpp
  #connectionslistjob.cpp

)

kde4_add_library(kfbapi SHARED ${kfbapi_SRCS})

set(CMAKE_INSTALL_NAME_DIR ${LIB_INSTALL_DIR})

# Yes, QJSON_LIBRARIES and QJSON_LIBRARY are both needed, as otherwise it will break either
# on Linux or on Mac.
target_link_libraries(kfbapi
  ${KDE4_KDECORE_LIBS}
  ${KDE4_KDEUI_LIBS}
  ${QT_QTGUI_LIBRARY}
  ${QT_QTWEBKIT_LIBRARY}
  ${KDE4_KDEWEBKIT_LIBS}
  ${KDE4_KIO_LIBS}
  ${QJSON_LIBRARIES}
  ${QJSON_LIBRARY}
  ${qjson_LIBRARIES} # for Debian
  ${KDEPIMLIBS_KABC_LIBS}
  ${KDEPIMLIBS_KPIMUTILS_LIBS}
  ${KDEPIMLIBS_KMIME_LIBS}
)


if(KDEPIM_44_COMPAT)
  target_link_libraries(kfbapi ${KDEPIMLIBS_KCAL_LIBS})
else(KDEPIM_44_COMPAT)
  target_link_libraries(kfbapi ${KDEPIMLIBS_KCALCORE_LIBS})
endif(KDEPIM_44_COMPAT)

set_target_properties(kfbapi PROPERTIES VERSION ${KFACEBOOK_LIB_VERSION} SOVERSION ${KFACEBOOK_LIB_SOVERSION})
install(TARGETS kfbapi ${INSTALL_TARGETS_DEFAULT_ARGS})

install( FILES
  alleventslistjob.h
  allnoteslistjob.h
  allpostslistjob.h
  appinfo.h
  authenticationdialog.h
  commentinfo.h
  ${CMAKE_BINARY_DIR}/config.h
  eventjob.h
  eventinfo.h
  eventslistjob.h
  facebookjobs.h
  friendlistjob.h
  friendjob.h
  getcommentsjob.h
  getlikesjob.h
  libkfbapi_export.h
  likeinfo.h
  listjobbase.h
  noteinfo.h
  noteslistjob.h
  notejob.h
  noteaddjob.h
  notificationinfo.h
  notificationslistjob.h
  notificationsmarkreadjob.h
  pagedlistjob.h
  photojob.h
  postinfo.h
  postjob.h
  postaddjob.h
  postslistjob.h
  propertyinfo.h
  userinfojob.h
  userinfo.h
  util.h
  #connectioninfo.h
  #connectionslistjob.h

 DESTINATION ${INCLUDE_INSTALL_DIR}/libkfbapi COMPONENT Devel
)
