CXX	=	g++
CFLAGS  = 	-g3
LIBS	=	-L../../../lib -lcykohonen -lcycommon
INCPATH =	-I../ -I../../common
DESTDIR = 	../../../lib/
TARGET	=	cykohonen_test \
		cykohonen_test2 \
		cykohonen_test3

all: $(TARGET) 

cykohonen_test:
	$(CXX) $(CFLAGS) $(INCPATH) -o $(DESTDIR)cykohonen_test cykohonen_test.cpp $(LIBS) -Wl,-rpath,./

cykohonen_test2:
	$(CXX) $(CFLAGS) $(INCPATH) -o $(DESTDIR)cykohonen_test2 cykohonen_test2.cpp $(LIBS) -Wl,-rpath,./

cykohonen_test3:
	$(CXX) $(CFLAGS) $(INCPATH) -o $(DESTDIR)cykohonen_test3 cykohonen_test3.cpp $(LIBS) -Wl,-rpath,./

clean: 
	rm -f cykohonen_test 
	rm -f cykohonen_test2 
	rm -f cykohonen_test3 

distclean: clean
	rm -f core core.*