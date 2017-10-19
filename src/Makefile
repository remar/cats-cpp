AR := ar
CPPFILES := $(wildcard *.cpp)
CXXFLAGS := `sdl2-config --cflags` -std=c++11
OFILES := $(CPPFILES:.cpp=.o)

libcats.a: $(OFILES)
	$(AR) rvs $@ $^
	mkdir -p ../lib
	mv $@ ../lib
	mkdir -p ../include
	cp Cats.h ../include

clean:
	@rm *.o
	@rm -rf ../lib
	@rm -rf ../include
