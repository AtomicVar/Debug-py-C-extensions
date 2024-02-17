# Debug Python's C/C++ extensions

You can easily debug Python's C/C++ extensions using GDB/LLDB. Here's a demo.

You need to install [pybind11](https://github.com/pybind/pybind11) to build and run this project.

## How to build

```sh
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
```

This will build a `hello` extension module in `build/`, e.g. `build/hello.cpython-38-darwin.so` in macOS.

## How to run/debug

Here's a simple Python script that loads the `hello` extension module and calls the `hello` function:

```python
# main.py
import build.hello as hello

hello.hello(42)
```

Set a breakpoint using VS Code GUI to `hello.cpp`'s `hello` function, and click
the Debug button of VS Code. You can check the debug config: [.vscode/launch.json](/.vscode/launch.json).

![debug.png](./debug.png)

You can also use GDB/LLDB CLI to debug it:

```sh
lldb python main.py
(lldb) target create "python"
Current executable set to '/Users/guoshuai/mambaforge/envs/mlx-dev-py38/bin/python' (arm64).
(lldb) settings set -- target.run-args  "main.py"
(lldb) b hello.cpp:4
Breakpoint 1: no locations (pending).
WARNING:  Unable to resolve breakpoint to any actual locations.
(lldb) r
Process 24624 launched: '/Users/guoshuai/mambaforge/envs/mlx-dev-py38/bin/python' (arm64)
1 location added to breakpoint 1
Process 24624 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = breakpoint 1.1
    frame #0: 0x00000001006d46cc hello.cpython-38-darwin.so`hello(x=42) at hello.cpp:4:6
   1    #include <pybind11/pybind11.h>
   2   
   3    int hello(int x) {
-> 4        x++;
   5        printf("Hello, %d\n", x);
   6        return x;
   7    }
Target 0: (python) stopped.
```