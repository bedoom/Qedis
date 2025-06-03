cmake_minimum_required(VERSION 3.25)

project(QEDIS)

subdirs(QBase)
# subdirs()

set(QEDIS_CLUSTER 0)
set(USE_ZOOKEEPER 0)
set(CONFIG_DEBUG 0)

add_definitions(-DQEDIS_CLUSTER=${QEDIS_CLUSTER})
add_definitions(-DUSE_ZOOKEEPER=${USE_ZOOKEEPER})
add_definitions(-DCONFIG_DEBUG=${CONFIG_DEBUG})
if(${QEDIS_CLUSTER} EQUAL 1)
    subdirs(QSentinel)
endif()
