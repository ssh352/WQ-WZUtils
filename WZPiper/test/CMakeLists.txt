SET(SOCKET_FILE tcp udp)
SET(TCP_FILE client)
SET(UDP_FILE server)
SET(GTEST_SO pthread)
SET(UTILS_SO iniparser logger glog)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")  

LINK_DIRECTORIES(${LIBRARY_OUTPUT_PATH})
LINK_DIRECTORIES(../../WZConfigReader)
LINK_DIRECTORIES(../../WZLogger/lib)

ADD_EXECUTABLE(${TCP_FILE} ${TCP_FILE}.cpp)
ADD_EXECUTABLE(${UDP_FILE} ${UDP_FILE}.cpp)

TARGET_LINK_LIBRARIES(${TCP_FILE} ${GTEST_SO} ${SOCKET_FILE} ${UTILS_SO})
TARGET_LINK_LIBRARIES(${UDP_FILE} ${GTEST_SO} ${SOCKET_FILE} ${UTILS_SO})
