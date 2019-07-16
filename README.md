# blackengine
Blackengine - YET another home grown 3D game engine. 

## Features
 - Crossplatform
 - Plugin based
 - Modern (c++ 17)
 - Fast
 - Simple API for developers

## Building using cmake and conan
This instruction is for Linux users. Windows user should do naturally same things. Instructions for Mac users can be found below.

You need to install Conan package manager to build the project.

### Step 1. Clone.

```
git clone https://github.com/JorgenPo/blackengine.git 
cd blackengine
```

### Step 2. Download Conan dependencies.

First, create building directory. You could create it outside sources if you want.
```
mkdir build
cd build
```

Second, we need to download project dependencies using conan:
```
conan install ..
```

**If you created the build folder in different location, then you need to change ".." to your blackengine source directory**

### Step 3. Generate build files
```
cmake -DCMAKE_INSTALL_PREFIX=<installation directory> ..
```

**Don't forget to change "installation directory" to directory where you want to install blackengine**

### Step 4. Make and make install
```
make -j2 install
```
After this step blackengine will be installed at <installation directory>.


## Build using Xcode on MacOS

### Step 1 - 2 same as on Linux and Windows (see above)

### Step 3. Generate Xcode project
```
cmake -DCMAKE_INSTALL_PREFIX=<installation directory> -G Xcode..
```

If you get following error 
```
No CMAKE_C_COMPILER could be found
No CMAKE_CXX_COMPILER could be found.
```

try run this command 

```
sudo xcode-select --reset
```

then repeat step

### Step 4. Open project in Xcode

Now you can work with project like with any other Xcode project. 

## Examples
There is examples of using blackengine in /examples folder of installation directory. Look for it.

## Why
This is a study project for learning game engine development

## Contributing 
If you found a bug, please fill an issue!
All contributing appreciated. All PRs will be reviewed and (probably) merged. 
