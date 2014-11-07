include(ECMMarkAsTest)
find_package(ECM 1.0.0 REQUIRED NO_MODULE)

find_package(Qt5 5.2.0 CONFIG REQUIRED Test)
find_package(AccountsQt5 1.10 CONFIG)
find_package(SignOnQt5 8.55 CONFIG)
find_package(KAccounts)

remove_definitions(-DQT_NO_CAST_FROM_ASCII)

if(${AccountsQt5_FOUND} AND ${SignOnQt5_FOUND} AND ${KACCOUNTS_FOUND})
    add_definitions(-DHAVE_KACCOUNTS=1)

    include_directories (${ACCOUNTSQT_INCLUDE_DIRS}
                        ${SIGNONQT_INCLUDE_DIRS}
                        ${KACCOUNTS_INCLUDE_DIRS}
    )

endif()


macro(kfbapi_executable_tests)
  foreach(_testname ${ARGN})
    add_executable(${_testname} ${_testname}.cpp)
    target_link_libraries(${_testname} Qt5::Test Qt5::Core Qt5::Xml KF5::FbAPI KF5::CoreAddons)

    if(${AccountsQt5_FOUND} AND ${SignOnQt5_FOUND} AND ${KACCOUNTS_FOUND})
        target_link_libraries(${_testname} ${ACCOUNTSQT_LIBRARIES} ${SIGNONQT_LIBRARIES} ${KACCOUNTS_LIBRARIES})
    endif()

    ecm_mark_as_test(${_testname})
  endforeach(_testname)
endmacro()

kfbapi_executable_tests(
    postsjobtest
    notificationtest
    userinfotest
)