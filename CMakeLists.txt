cmake_minimum_required (VERSION 2.6)

project( myHardwareProject ) 
include_directories( include ) 


add_library( myHardware SHARED src/MyHardware.cpp )

add_library( myHardwareS STATIC src/MyHardware.cpp )

add_executable( cpu app/cpu.cpp )

target_link_libraries( cpu myHardwareS ) 
