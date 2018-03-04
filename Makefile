src = $(wildcard *.c)
obj = $(src:.c=.o)
bin = test

GLSLANG = glslangValidator

CFLAGS = -pedantic -Wall -g -DGL_GLEXT_PROTOTYPES
LDFLAGS = -lGL -lGLU -lglut -lm

$(bin): $(obj) spirv/vertex.spv spirv/pixel.spv
	$(CC) -o $@ $(obj) $(LDFLAGS)

spirv/vertex.spv: vertex.glsl
	$(GLSLANG) -V -S vert -o $@ $<

spirv/pixel.spv: pixel.glsl
	$(GLSLANG) -V -S frag -o $@ $<

.PHONY: clean
clean:
	rm -f $(obj) $(bin) spirv/*.spv
