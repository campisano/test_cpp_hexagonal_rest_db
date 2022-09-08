.PHONY: all
all:
	mkdir -p build
	cd build && cmake -Wno-dev ..
	$(MAKE) -C build

.PHONY: clean
clean:
	test ! -d build && true || $(MAKE) -C build clean
