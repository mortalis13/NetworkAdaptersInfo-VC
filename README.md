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

      call "c:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat"
      cl ipconf.cpp Iphlpapi.lib ws2_32.lib

If the same console window is used for multiple builds, the `vcvarsall.bat` can be called only once before the first build.
