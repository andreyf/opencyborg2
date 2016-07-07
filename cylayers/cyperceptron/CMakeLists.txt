set ( cyperceptron_src cyperceptron.cpp )

include_directories(../common)

add_library ( cyperceptron SHARED ${cyperceptron_src} )

