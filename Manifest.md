
# Manifest for the **queenbee** project #

## Current situation (01/01/2016) ##

As of 1st of January 2016, support for Optimus on Linux is still limited. The most advanced tool available at the moment is Bumblebee. Bumblebee allows to run a desktop on an integrated graphic card and run certain application on the dedicated GPU. However it is up to the end user to choose which application runs on which GPU. Developers and/or package maintainers are not the one determining if their application should or should not run on a dedicated GPU.

## Goal of this project ##

The goal of this project is to allow application developers to enable their application to run on a dedicated GPU if one is available, if it is sensible to do so and if it is possible to do so.

The solution to this problem is to create a application wrapper like Bumbleebee's **optirun** but does not require Bumblebee to be installed and does not require the system to have hybrid graphics. It stems that the application wrapper should follow the following rules:

1. The application does not depend on Bumbleebee, Prime or any hybrid graphics management tool to be installed
2. The application wrapper should be lightweight, by which I mean it should not delay the launch of the application.
3. The license of the **queenbee** project should be permissive.
4. The application should have little dependencies so developers are safe to assume it is already preinstalled on pretty much every distribution.

## Overview of the application wrapper ##

The application wrapper logic can be summed up as follows:

```shell
if system has hybrid graphics
then
  if app should execute on dedicated GPU
  then
    if bumblebee
    then
      execute app via optirun
    elif xrandr gpu offloading
      excute app via xrandr gpu offloading
    then
      # Direct application execution
      execute app
    fi
  else
  fi
else
  # Direct application execution
  execute app
fi
```

Whilst this seems simple there is a couple of caveats which complexifies the project:
1. Whether an application should or shouldn't execute on a dedicated GPU may not be a simple. Graphic intensive games almost always need dedicated GPU graphics. However some applications may be ok running on integrated graphics if those are good enough. This project aims at supporting this subtlety the best it can.
2. Whilst developers are expected to use this tool to their best, it could happen that they don't use it correctly. Even worse some applications on some Linux systems may not work well on some graphic chips. This project also aims at allowing end users to override the behaviour.

## Marketing ##

It is crucial for this project success to have good visibility amongst Linux developers. It is essential to both advertise this project and also ensure it is highly reliable.
