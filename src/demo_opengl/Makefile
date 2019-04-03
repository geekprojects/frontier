
TGT=demo_opengl
SRCS=main.cpp
OBJS=$(SRCS:.cpp=.o)

all: $(TGT)

clean:
	rm -f $(TGT) $(OBJS)


$(TGT): $(OBJS)
	gcc $(OBJS) -o $(TGT) `pkg-config libfrontier --libs` -framework GLUT -framework OpenGL -lstdc++ -fsanitize=address -lfrontier-opengl

.cpp.o:
	gcc -c $< -o $@ `pkg-config libfrontier --cflags` -Wno-deprecated-declarations -fsanitize=address


