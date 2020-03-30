## Build

```zsh
cmake ${src-dir-path} -DBUILD_BND=OFF -DBUILD_TOOLS=OFF
make -j
```


* Some build options are as follows

```
option(BUILD_BND "build-bnd" ON)
option(BUILD_PND "build-pnd" ON)
option(BUILD_ALL "build-all" ON)
option(BUILD_TOOLS "build-tools" ON)
```

## Run

