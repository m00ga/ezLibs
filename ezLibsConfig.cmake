foreach(component ${ezLibs_FIND_COMPONENTS})
    include(${CMAKE_CURRENT_LIST_DIR}/ezLibs-${component}-config.cmake)
endforeach()
