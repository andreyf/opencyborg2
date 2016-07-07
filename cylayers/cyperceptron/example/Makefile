CXX	=	g++
CFLAGS  = 	-g3
LIBS	=	-L../../../lib -lcyperceptron -lcycommon
INCPATH =	-I../ -I../../common
DESTDIR = 	../../../lib/

TARGET	=	cyperceptron_test \
		cyperceptron_test2 \
		cyperceptron_test5 \

all: $(TARGET) 

cyperceptron_test:
	$(CXX) $(CFLAGS) $(INCPATH) -o $(DESTDIR)cyperceptron_test cyperceptron_test.cpp $(LIBS) -Wl,-rpath,./

cyperceptron_test2:
	$(CXX) $(CFLAGS) $(INCPATH) -o $(DESTDIR)cyperceptron_test2 cyperceptron_test2.cpp $(LIBS) -Wl,-rpath,./

cyperceptron_test5:
	$(CXX) $(CFLAGS) $(INCPATH) -o $(DESTDIR)cyperceptron_test5 cyperceptron_test5.cpp $(LIBS) -Wl,-rpath,./

clean: 
	rm -f cyperceptron_test 
	rm -f cyperceptron_test2 
	rm -f cyperceptron_test5

distclean: clean
	rm -f core core.*
