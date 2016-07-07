set ( cyperceptron_src cyperceptron.cpp )

include_directories(../common)

add_library ( cyperceptron shared ${cyperceptron_src} )

