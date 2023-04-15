# About

- A minimally configured dynamic transformation engine for images, implemented in Halide. https://halide-lang.org/

- [Halide](https://halide-lang.org/) で実装した、最小構成の画像動的変換サーバです。

# How to build halide image encoder

```shell
cmake -DCMAKE_BUILD_TYPE=Release
make
```

## Usage

```shell
./dynamicImageEncoder/resizer ${IMAGE_PATH} 100 200
```

# Run

```shell
$ cd api
$ go run main.go
```

And then access to the bellow links.

- http://localhost:8080/image?f=1.jpeg
- http://localhost:8080/image?f=1.jpeg&w=100
- http://localhost:8080/image?f=1.jpeg&w=100&h=100

# Workaround

## LLVM Error : `Could not find a package configuration file provided by "LLVM" (requested
  version 15.0.7) with any of the following names:`

```shell
export LLVM_DIR=/opt/homebrew/Cellar/llvm@15/15.0.7/lib/cmake
# $ brew ls llvm
# or brew ls llvm@15
```
