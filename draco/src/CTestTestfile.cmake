# CMake generated Testfile for 
# Source directory: /home/brian/git/ray/draco/src
# Build directory: /home/brian/git/ray/draco/src
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Test "UnitTests")
subdirs(TextureLoader)
subdirs(AssetLoader)
subdirs(WorldModel)
subdirs(DragonMath)
subdirs(Main)
subdirs(RayTracer)
