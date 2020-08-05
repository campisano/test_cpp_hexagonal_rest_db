.PHONY: all
all:
	cmake -B build -S .
	$(MAKE) -C build

.PHONY: clean
clean:
	$(MAKE) -C build clean
