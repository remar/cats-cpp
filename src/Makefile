AR := ar
CPPFILES := $(wildcard *.cpp)
CXXFLAGS := `sdl2-config --cflags` -std=c++11
OFILES := $(CPPFILES:.cpp=.o)

libcats.a: $(OFILES)
	$(AR) rvs $@ $^

clean:
	@rm *.o libcats.a
