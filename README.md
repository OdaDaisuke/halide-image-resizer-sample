# About

- A minimally configured dynamic transformation engine for images, implemented in Halide. https://halide-lang.org/

- [Halide](https://halide-lang.org/) で実装した、学習用の最小構成画像動的変換サーバです。

Thanks @octu0 san.

# Usage

```shell
$ make generate
$ go run main.go
```

And then access to the bellow links.

- http://localhost:8080/image?f=1.png&w=1200&h=1100
- http://localhost:8080/image?f=2.png&w=1800&h=1500

# Workaround

### LLVM Error : `Could not find a package configuration file provided by "LLVM" (requested version 15.0.7) with any of the following names:`

Set `LLVM_DIR`.

```shell
export LLVM_DIR=/opt/homebrew/Cellar/llvm@15/15.0.7/lib/cmake
# $ brew ls llvm
# or brew ls llvm@15
```
