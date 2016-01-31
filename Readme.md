**queenbee** is an application wrapper which executes an application on a dedicated GPU, if the system has hybrid graphics, supports GPU offloading technology such as **Bumblebee** and if offloading is sensible.

Basic usage works as such
```shell
queenbee app
```

for instance
```shell
queenbee glxgears -info
```

will execute
```shell
optirun glxgears -info
```
if the system has hybrid graphics and if Bumblee is installed.

# Building #

To build **queenbee** you need:
1. Python
2. scons

To build in debug mode
```shell
scons --build-debug
```

To build in debug mode
```shell
scons --build-release
```

To clean the project run
```shell
scons -c
```
