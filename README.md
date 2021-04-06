# ipconf

Shows information about network adapters in the following format:

```
[IP]: ADAPTER_NAME_1
[IP]: ADAPTER_NAME_2
...
```

An alternative to `ipconfig` command for **Windows**.

# Build
- install **Visual Studio 2019** with the **C++** module
- run `r.bat` to build and run the executable
- or use the `cl` command line tool:

      cl ipconf.cpp Iphlpapi.lib ws2_32.lib
