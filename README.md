This repository includes all of the student material for the SciPy 2014 workshop "Integrating Python and C++ with Boost.Python". Participants should be sure to clone this repository to their working machine 
prior to attending the workshop. They should also be sure to verify that their system can compile and link Boost.Python-based programs and shared libraries.

# **Pre-Workshop Instructions**

The primary activity of this workshop is writing C++ code and compiling it into Python modules. As such, in order to get the most out of this workshop, each participant should bring their own laptop, 
though sharing a system between two people should work reasonably well.

We will spend as little time as possible - ideally none - on installing Python, Boost.Python, compilers, etc. What follows are instructions for setting up your system and verifying that it's ready for the 
workshop.

# The easy way: Ready-to-go virtual machine image with Ubuntu #

The simplest way to make sure your system is ready for the workshop is to use the VM we've prepared for it. The VM comes with a full Ubuntu installation along with all of the libraries and build tools that 
you need to do the exercises.

The image is packaged as an OVF 1.0 archive (.ova) that should run on most of the popular virtualization systems.

You can [**download the image here**](https://www.dropbox.com/s/vs4oh9lsaiogtfy/BoostPythonWorkshop.ova).

Once you boot the image, you should be taken to an Ubuntu desktop. From there, start a terminal (you may need to use alt-F1 to see the launcher) and type:

```
#!bash

% cd workshop/exercises
% make plumbing_test
% plumbing_test
<information on Python version>
% make smoke_test
% python3 -c "import smoke_test; print(smoke_test.test())"
42
```

If all of this works, then your system is ready for the workshop.

## Notes

 * There's been a report that this image crashes on VMWare, but it's known to work properly on several VirtualBox installations.

# Setting up a linux system #
Using your distributions package management system, first install the following packages:

 * **[Boost.Python](http://boost.org)** This may just be part of a "boost" package, or it may be on its own. Be sure to install the "dev" package with headers.
 * **Python** Use the version that matches the Boost.Python you installed. This will probably be Python 2.7, but there's no guarantee of that.
 * A C++ compiler. `g++` is probably the best option.
 * An editor of some sort.
 * **[git](http://git-scm.com/)** To clone the exercises
 * **make** To build the exercises

Once you have all of this installed, you need to clone the git repository containing the exercises.

```
#!bash

% git clone git@bitbucket.org:sixty-north/scipy2014_boost_python_workshop_student_material.git workshop
% cd workshop
```

Once this is in place, you may need to modify `make.common` to match your system. It should be fairly self-explanatory.

Next, you should run a few test to make sure the system is ready:

```
#!bash
% make plumbing_test
% plumbing_test
<information on Python version>
% make smoke_test
% python -c "import smoke_test; print(smoke_test.test())"
42
```

Note that the Python executable may be `python3` or perhaps even `python2` depending on your distribution and configuration.

## Notes

 * On Ubuntu 12 (Precise) the boost.python package you should install is libboost-python1.46-dev.
 * On Ubuntu 14 (Trusty) the boost.python package you should install is libboost-python1.55-dev. This can make libraries for Python 2.7, 3.3, and 3.4.
 * On Ubuntu 14 you may need to update the `PYTHON_EXTENSION_SUFFIX` in `make.common` to `.so` rather than relying on `python3-config`. This is because `python3-config --extension-suffix` reports `@SO@` rather than `.so` for some reason.  

# Setting up a Mac OS X system #

There are a number of ways to set up a Mac OS X system, including compiling everything yourself, [homebrew](http://brew.sh/), and [macports](http://www.macports.org/). The homebrew approach is known to 
work, but there's no reason that the others shouldn't. Ultimately, you need to make sure you install the following things:

 * **[Boost](http://boost.org)** Including Boost.Python and all development headers
 * **[Python](http://python.org)** 
 * A c++ compiler
 * **make**
 * **[git](http://git-scm.com/)**
 * an editor

Once these are installed, clone the workshop git repository:

```
#!bash
git clone git@bitbucket.org:sixty-north/scipy2014_boost_python_workshop_student_material.git workshop
cd workshop
```

You may now need to edit `make.common` to match your system. There is a `make.common.OSX` that should be closer to a standard OSX system than the default `make.common`, so you can 
copy it over or use it as a template if you want.

Next, build and run a few tests:

```
#!bash
% make plumbing_test
% plumbing_test
<information on Python version>
% make smoke_test
% python -c "import smoke_test; print(smoke_test.test())"
42
```

Note that the Python executable may be `python3` or perhaps even `python2` depending on your configuration.

# Windows #

For windows we have provided a VisualStudio 2013 solution as part of the course material. To use this, you'll need to install:

 * **[git](http://git-scm.com/)**
 * **[Python](http://python.org)** Version 2.7 or 3.x
 * **[Boost](http://boost.org)** Including Boost.Python and development headers
 * [VisualStudio 2013](http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx)

Once this is all in place, clone the git repository:

```
> git clone git@bitbucket.org:sixty-north/scipy2014_boost_python_workshop_student_material.git workshop
```

(Note that you can also use GUI git tools as well.) 

The VisualStudio project is in `workshop/vs`. Open the solution in VisualStudio and build the `plumbing_test` and `smoke_test` projects. You should build
"release" versions.

Then in the directory `workshop/vs/BoostPythonWorkshop/Release`, check the two items you just built:

```
> plumbing_test.exe
<information about your Python version>
> python -c "import smoke_test; print(smoke_test.test())"
42
```

If this all works, then you're ready for the workshop.