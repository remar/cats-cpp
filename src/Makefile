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

doc:
	doxygen ../doc/api/Doxyfile

clean:
	@rm -f *.o libcats.a *.d *~
	@(cd ../doc/api && rm -rf html latex doxygen_sqlite3.db)
