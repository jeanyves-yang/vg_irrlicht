CPPFLAGS = -I/usr/include/irrlicht
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused-parameter

vg_irrlicht: main.o
	g++ $^ -o $@ -lIrrlicht

clean:
	@rm -f vg_irrlicht *.o
