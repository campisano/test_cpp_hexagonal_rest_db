.PHONY: all
all:
	mkdir -p build
	cd build && cmake ..
	$(MAKE) -C build

.PHONY: clean
clean:
	$(MAKE) -C build clean
