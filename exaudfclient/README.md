# What is the exaudfclient?

The exaudfclient connects to the database via [ZeroMQ](http://zeromq.org/) and fetches the tuples which then get processed by the user-defined functions (UDFs). Currently, the exaudfclient supports UDFs in Python. Further languages can be integrated via language binding between C/C++ and the desired language. Python 3 uses [SWIG](http://www.swig.org/) for the language binding.

# How to build the exaudfclient?

## Prerequisites

For the build system:

- bazel-7.2.1 for more details see [Bazel documentation](https://docs.bazel.build/versions/master/install.html)

The exaudfclient was tested with the following versions of its dependencies:

- swig-2.0.4 or swig-3.0.12
- protobuf 3.12.4
    - we need both compiler and library, they must be in the same version
    - don't install two version, because then its possible that you compile against the wrong header or link against wrong library
- zmq 4.3.4

For the language support:

- Python 3.10 for pythoncontainer
    - for Python 3 the build requires [Numpy](https://www.numpy.org/) and [Pandas](https://pandas.pydata.org/) in addition for the Pandas Dataframe Support

## Start a build

The exaudfclient is a Python project with a C++ runner. It uses [Bazel](https://docs.bazel.build/versions/master/bazel-overview.html) to build the local Python VM against the shared runner base from `exasol/udf-runner-cpp`. Set the Python library and header locations through environment variables.

For executing the build locally, you can use the script 

    build_locally.sh <options> <defines> <targets>
    
which reads the environment variables from a .env file. The template .env.template resides in the git repository. Please, copy it and rename it .env . **The .env file is listed in the .gitignore, so don't check it in.** 

If your using docker to build the code you should use the script 

    build.sh <options> <defines> <targets>
    
and set the Environment Variables via Docker.

Both build script can receive parameters, such as Bazel commandline parameter, Bazel define (--define {key}={value}) and targets. 

With Bazel defines you can specify which language support is actually compiled into you exaudfclient executbale. The currently supported defines are

    --define python=true


The main targets is //:exaudfclient.

## Visualizing the build dependencies

Bazel allows to query the dependencies of a target. Furthermore, it can export the dependencies as .dot file. With Graphviz you can generate figures from the .dot file. The script visualize_deps.sh and visualize_all.sh wrap this process. The script visualize_all.sh visualizes the dependencies of the main targets //:exaudfclient. The script visualize_deps.sh visualizes the dependencies of given targets.

    visualize_deps.sh <targets>

# How is the exaudfclient structured?

The local code contains the main function in [exa_udfclient.cc](exa_udfclient.cc) and the Python VM. The shared libexaudf transport, loader, ZeroMQ, and Protobuf dependencies come from the pinned `exasol/udf-runner-cpp` Bazel module and load in a separate linker namespace.

The usage of multiple linker namespace requires some precautions in the build process and in the implementation. 

## Precautions in the build process

Do not link the Python VM directly against the shared transport implementation: use only the `@exaudfclient_base//exaudflib:header` and `@exaudfclient_base//exaudflib:exaudflib-deps` targets. This keeps ZeroMQ and Protobuf out of the Python VM linker namespace.

## Precautions in the implementations

- Make you familiar with linker namespaces and with the library libdl.so
- Deconstructors and different linker namespace can be fun, not! If you need to use data in one namespace which was created in the other namespace make sure to store it module wide static variables, because the lifetime of these variables is the lifetime of the program. Furthermore, static variable decleration should be in the module which creates the data and the module in the other namespace should only use a pointer to this data which is also stored in a static variable in a module in this namespace.

You can find more information about linking and linkers [here](https://www.lurklurk.org/linkers/linkers.html).
