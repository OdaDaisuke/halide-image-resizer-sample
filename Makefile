.PHONY: generate
generate:
	clang++ \
		-g \
		-arch arm64 \
		-I/opt/homebrew/Cellar/halide/15.0.1/include/ \
		-I/opt/homebrew/Cellar/halide/15.0.1/share/tools/ \
		-L/opt/homebrew/Cellar/halide/15.0.1/lib/ \
		-I/opt/homebrew/Cellar/jpeg/9e/include/ \
		-L/opt/homebrew/Cellar/jpeg/9e/lib/ \
		-I/opt/homebrew/Cellar/libpng/1.6.39/include/ \
		-L/opt/homebrew/Cellar/libpng/1.6.39/lib/ \
		-lHalide \
		-lpthread \
		-ldl \
		-lz \
		-std=c++17 \
		-o a.out resizer.cpp
	./a.out
