AR := ar
CPPFILES := $(wildcard *.cpp)
DEPFILES := $(patsubst %.cpp,%.d,$(CPPFILES))
CXXFLAGS := `sdl2-config --cflags` -std=c++11 -Wall
OFILES := $(CPPFILES:.cpp=.o)

libcats.a: $(OFILES)
	$(AR) rvs $@ $^

-include $(DEPFILES)

%.o: %.cpp Makefile
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	@rm -f *.o libcats.a *.d *~
