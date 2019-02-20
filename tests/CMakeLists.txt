set(CMAKE_C_FLAGS "-O0 -g")
set(CMAKE_CXX_FLAGS "-O0 -g")
# minimal target
 add_executable(minimal minimal.cpp)
 target_link_libraries(minimal ei eibase ${Allegro_LIBRARIES} m)


# Targets disabled until the basic functionalities of the library are implemented

add_executable(frame frame.cpp
../include/hw_interface.h
    ../include/ei_event.h
    ../include/keycodes.h
    ../src/ei_placer.cpp 
    ../include/ei_geometrymanager.h 
    ../src/ei_widget.cpp 
    ../src/ei_frame.cpp 
    ../include/ei_widget.h
    ../include/ei_widgetdatabank.h
    ../include/ei_widgetplacerdata.h
    ../src/ei_widgetdatabank.cpp
    ../src/ei_widgetplacerdata.cpp
    ../src/ei_application.cpp
    ../src/ei_eventmanager.cpp
    ../include/ei_eventmanager.h)
target_link_libraries(frame ei eibase ${Allegro_LIBRARIES} m)

#add_executable(button button.cpp
#    ../include/hw_interface.h
#    ../include/ei_event.h
#    ../include/keycodes.h
#    ../src/ei_placer.cpp 
#    ../include/ei_geometrymanager.h 
#    ../src/ei_widget.cpp 
#    ../src/ei_frame.cpp 
#    ../include/ei_widget.h
#    ../include/ei_widgetdatabank.h
#    ../include/ei_widgetplacerdata.h
#    ../src/ei_widgetdatabank.cpp
#    ../src/ei_widgetplacerdata.cpp
#    ../src/ei_application.cpp
#    ../src/ei_eventmanager.cpp
#    ../include/ei_eventmanager.h
#)
#target_link_libraries(button ei eibase ${Allegro_LIBRARIES} m)

# add_executable(toplevel toplevel.cpp)
# target_link_libraries(toplevel ei eibase ${Allegro_LIBRARIES} m)


# Unit tests
add_executable(
    unit_tests unit_tests.cpp 
    ../include/hw_interface.h
    ../include/ei_event.h
    ../include/keycodes.h
    ../src/ei_placer.cpp 
    ../include/ei_geometrymanager.h 
    ../src/ei_widget.cpp 
    ../src/ei_frame.cpp 
    ../src/ei_button.cpp 
    ../include/ei_widget.h
    ../include/ei_widgetdatabank.h
    ../include/ei_widgetplacerdata.h
    ../src/ei_widgetdatabank.cpp
    ../src/ei_widgetplacerdata.cpp
    ../src/ei_application.cpp
    ../src/ei_eventmanager.cpp
    ../include/ei_eventmanager.h
)
target_link_libraries(unit_tests ei eibase ${Allegro_LIBRARIES} m)

enable_testing()
ms_add_catch_tests(unit_tests) 
