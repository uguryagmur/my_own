CFLAGS = -std=c++17 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

VulkanRenderer: create_bin main.cpp
	g++ $(CFLAGS) main.cpp -o bin/renderer $(LDFLAGS) 

create_bin:
	mkdir -p bin

.PHONY: test clean
test: VulkanRenderer
	./bin/renderer

clean:
	rm -rf bin

