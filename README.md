# Build

```shell
cmake -DCMAKE_BUILD_TYPE=Release
make
```

# Usage

./dynamicImageEncoder/resizer ./sample_images/1.jpeg 100 200

# Workaround

## LLVM

Error : `Could not find a package configuration file provided by "LLVM" (requested
  version 15.0.7) with any of the following names:`

```shell
export LLVM_DIR=/opt/homebrew/Cellar/llvm@15/15.0.7/lib/cmake
# $ brew ls llvm
# or brew ls llvm@15
```
