project(lab_deps)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE on)
include(ExternalProject)
include(ProcessorCount)

if (NOT INSTALL_ROOT)
message("\
**************************
INSTALL_ROOT must be defined
INSTALL_ROOT = path to where to install the compiled software, e.g, /home/myname/root
**************************")
  message(FATAL_ERROR)
endif()
message("INSTALL_ROOT = ${INSTALL_ROOT}")

ProcessorCount(JJ)

#***********************************
# Downloads
#***********************************
# gtest
ExternalProject_Add(gtest-download
  PREFIX downloads/gtest-download
  URL https://googletest.googlecode.com/files/gtest-1.7.0.zip
  DOWNLOAD_NAME gtest-1.7.0.zip
  URL_HASH SHA1=f85f6d2481e2c6c4a18539e391aa4ea8ab0394af
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
#OpenBlas
ExternalProject_Add(openblas-download
  PREFIX downloads/openblas-download
  URL http://github.com/xianyi/OpenBLAS/archive/v0.2.14.tar.gz
  DOWNLOAD_NAME OpenBLAS-0.2.14.tar.gz
  URL_HASH SHA1=803ddccb727f2a94740136fb7cc8cef4a546ec98
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
# LAPACK
ExternalProject_Add(lapack-download
  PREFIX downloads/lapack-download
  URL http://www.netlib.org/lapack/lapack-3.5.0.tgz
  DOWNLOAD_NAME lapack-3.5.0.tgz
  URL_HASH SHA1=5870081889bf5d15fd977993daab29cf3c5ea970
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
# ARPACK-NG
ExternalProject_Add(arpack-ng-download
  PREFIX downloads/arpack-ng-download
  URL https://github.com/opencollab/arpack-ng/archive/3.2.0.tar.gz
  DOWNLOAD_NAME arpack-ng-3.2.0.tar.gz
  URL_HASH SHA1=128d04d82399c4174e1b32572845055aaaafef47
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# Armadillo
ExternalProject_Add(armadillo-download
  PREFIX downloads/armadillo-download
  URL http://sourceforge.net/projects/arma/files/armadillo-5.200.2.tar.gz
  DOWNLOAD_NAME armadillo-5.200.2.tar.gz
  URL_HASH SHA1=e7d8392dfcc7227c17bcdbe18ad88f2995115556
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# zlib
ExternalProject_Add(zlib-download
  PREFIX downloads/zlib-download
  #URL http://sourceforge.net/projects/libpng/files/zlib/1.2.8/zlib128-dll.zip/download?use_mirror=skylink&download=
  URL http://zlib.net/zlib128.zip
  #DOWNLOAD_NAME zlib-128-dll.zip
  DOWNLOAD_NAME zlib128.zip
  #URL_HASH MD5=42eccc2af5bac6b7a1188d7817d03549
  URL_HASH SHA1=5782f3539015ead310234fd8637a7fe78af3d16c
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# libiconv
ExternalProject_Add(libiconv-download
  PREFIX downloads/libiconv-download
  URL http://ftp.gnu.org/pub/gnu/libiconv/libiconv-1.14.tar.gz
  DOWNLOAD_NAME libiconv-1.9.2.tar.gz
  URL_HASH SHA1=be7d67e50d72ff067b2c0291311bc283add36965
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# libxml2
ExternalProject_Add(libxml2-download
  PREFIX downloads/libxml2-download
  URL ftp://xmlsoft.org/libxml2/libxml2-2.9.2.tar.gz
  DOWNLOAD_NAME libxml2-2.9.2.tar.gz
  URL_HASH SHA1=f46a37ea6d869f702e03f393c376760f3cbee673
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# boost
ExternalProject_Add(boost-download
  PREFIX downloads/boost-download
  URL http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz/download
  DOWNLOAD_NAME boost_1_59_0.tar.gz
  URL_HASH SHA1=5123209db194d66d69a9cfa5af8ff473d5941d97
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)

# mlpack
ExternalProject_Add(mlpack-download
  PREFIX downloads/mlpack-download
  URL http://www.mlpack.org/files/mlpack-1.0.12.tar.gz
  DOWNLOAD_NAME mlpack-1.0.12.tar.gz
  URL_HASH SHA1=ad4909e4978edf03ff70d5f3d884efb24b5992a4
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)


# libpca
ExternalProject_Add(libpca-download
  PREFIX downloads/libpca-download
  URL http://sourceforge.net/projects/libpca/files/libpca-1.3.3.tar.gz
  DOWNLOAD_NAME libpca-1.3.3.tar.gz
  URL_HASH SHA1=ead870a2a2c6ca4b62c180d782a051ee476fa030
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)



#***********************************
# Builds
#***********************************
# Gtest
ExternalProject_Get_Property(gtest-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(gtest-build
    PREFIX builds/gtest-build
    DEPENDS gtest-download
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=f85f6d2481e2c6c4a18539e391aa4ea8ab0394af
    BUILD_COMMAND make -j${JJ}    
    INSTALL_COMMAND ${CMAKE_COMMAND} -DINSTALL_ROOT=${INSTALL_ROOT} -DBUILD_DIR=${PROJECT_BINARY_DIR}/builds/gtest-build/src/gtest-build-build -P  ${CMAKE_CURRENT_LIST_DIR}/install_gtest.txt
#    INSTALL_COMMAND mkdir -p ${INSTALL_ROOT}/lib COMMAND cp libgtest.a libgtest_main.a ${INSTALL_ROOT}/lib COMMAND mkdir -p ${INSTALL_ROOT}/include COMMAND cp -r ../gtest-build/include/gtest ${INSTALL_ROOT}/include
  )
endif()

if (DEFINED WIN32 AND MSVC)
  ExternalProject_Add(gtest-build
    PREFIX builds/gtest-build
    DEPENDS gtest-download
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=f85f6d2481e2c6c4a18539e391aa4ea8ab0394af
    CMAKE_GENERATOR "Visual Studio 12 2013 Win64"
    CMAKE_ARGS -Dgtest_force_shared_crt=ON
    BUILD_COMMAND msbuild ALL_BUILD.vcxproj /p:configuration=debug COMMAND msbuild ALL_BUILD.vcxproj /p:configuration=release
    INSTALL_COMMAND ${CMAKE_COMMAND} -DDEBUG=debug -DRELEASE=release -DINSTALL_ROOT=${INSTALL_ROOT} -DBUILD_DIR=${PROJECT_BINARY_DIR}/builds/gtest-build/src/gtest-build-build -P  ${CMAKE_CURRENT_LIST_DIR}/install_gtest.txt
  )
endif()

# OpenBLAS
ExternalProject_Get_Property(openblas-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(openblas-build
    PREFIX builds/openblas-build
    DEPENDS openblas-download
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=803ddccb727f2a94740136fb7cc8cef4a546ec98
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make PREFIX=${INSTALL_ROOT} install
  )
endif()

if (DEFINED WIN32)
  ExternalProject_Add(openblas-build
    PREFIX builds/openblas-build
    DEPENDS openblas-download
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=803ddccb727f2a94740136fb7cc8cef4a546ec98
    CMAKE_GENERATOR "MSYS Makefiles"
    CMAKE_ARGS -DCMAKE_GNUtoMS=ON -DBUILD_SHARED_LIBS=ON
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make PREFIX=${INSTALL_ROOT} install
  )
endif()

# LAPACK
ExternalProject_Get_Property(lapack-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(lapack-build
    PREFIX builds/lapack-build
    DEPENDS lapack-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=5870081889bf5d15fd977993daab29cf3c5ea970
    CMAKE_GENERATOR "MSYS Makefiles"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT} -DCMAKE_PREFIX_PATH=${INSTALL_ROOT} -Wno-dev
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

if (DEFINED WIN32)
  ExternalProject_Add(lapack-build
    PREFIX builds/lapack-build
    DEPENDS lapack-download  
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=5870081889bf5d15fd977993daab29cf3c5ea970
    CMAKE_GENERATOR "MSYS Makefiles"
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT} -DCMAKE_PREFIX_PATH=${INSTALL_ROOT} -Wno-dev -DBUILD_SHARED_LIBS=ON -DCMAKE_GNUtoMS=ON  -DBLAS_LIBRARIES=${INSTALL_ROOT}/bin/libopenblas.dll
    BUILD_COMMAND mingw32-make -j$(JJ)
    INSTALL_COMMAND mingw32-make install
  )
endif()

# ARPACK-NG
ExternalProject_Get_Property(arpack-ng-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(arpack-ng-build
    PREFIX builds/arpack-ng-build 
    DEPENDS arpack-ng-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=128d04d82399c4174e1b32572845055aaaafef47
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT}
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

if (DEFINED WIN32)
  ExternalProject_Add(arpack-ng-build
    PREFIX builds/arpack-ng-build
    DEPENDS arpack-ng-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=128d04d82399c4174e1b32572845055aaaafef47
    CMAKE_GENERATOR "MSYS Makefiles"
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT} --host=x86_64-w64-mingw32 --with-blas=${INSTALL_ROOT}/bin/libopenblas.dll
    BUILD_COMMAND make
    INSTALL_COMMAND make install
  )
    
  add_custom_target(arpack-ng-finalize
    COMMAND sh -c "cd builds/arpack-ng-build/src/arpack-ng-build && x86_64-w64-mingw32-gfortran -shared  -Wl,--whole-archive ./SRC/.libs/libarpacksrc.a ./UTIL/.libs/libarpackutil.a -Wl,--no-whole-archive -O2   -o .libs/libarpack-2.dll -Wl,--enable-auto-image-base -Xlinker --out-implib -Xlinker .libs/libarpack.dll.a -Wl,-L${INSTALL_ROOT}/bin -llibopenblas"
    COMMAND sh -c "cd builds/arpack-ng-build/src/arpack-ng-build && cp .libs/libarpack.dll.a ${INSTALL_ROOT}/lib && cp .libs/libarpack-2.dll ${INSTALL_ROOT}/bin" 
  )
endif()

# Armadillo
ExternalProject_Get_Property(armadillo-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(armadillo-build
    PREFIX builds/armadillo-build
    DEPENDS armadillo-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=e7d8392dfcc7227c17bcdbe18ad88f2995115556
    BUILD_IN_SOURCE 1
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT} -DCMAKE_PREFIX_PATH=${INSTALL_ROOT}
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

if (DEFINED WIN32)
  ExternalProject_Add(armadillo-build
    PREFIX builds/armadillo-build
    DEPENDS armadillo-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=e7d8392dfcc7227c17bcdbe18ad88f2995115556
    BUILD_IN_SOURCE 1
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT} -DCMAKE_PREFIX_PATH=${INSTALL_ROOT}
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

# zlib
ExternalProject_Get_Property(zlib-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(zlib-build
    PREFIX builds/zlib-build
    DEPENDS zlib-download 
    URL ${download_dir}/${download_name}
    URL_HASH MD5=42eccc2af5bac6b7a1188d7817d03549
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT}
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

#if (DEFINED WIN32)
#  ExternalProject_Add(zlib-build
#    PREFIX builds/zlib-build
#    DEPENDS zlib-download 
#    URL ${download_dir}/${download_name}
#    URL_HASH MD5=42eccc2af5bac6b7a1188d7817d03549
#    BUILD_IN_SOURCE 1
#    CONFIGURE_COMMAND ""
#    BUILD_COMMAND ""
#    INSTALL_COMMAND cp zlib1.dll ${INSTALL_ROOT}/bin COMMAND cp include/zlib.h include/zconf.h ${INSTALL_ROOT}/include COMMAND cp lib/zdll.lib lib/zlib.def ${INSTALL_ROOT}/lib
#  )
#endif()
if (DEFINED WIN32)
  ExternalProject_Add(zlib-build
    PREFIX builds/zlib-build
    DEPENDS zlib-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=5782f3539015ead310234fd8637a7fe78af3d16c
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make -f win32/Makefile.gcc
    INSTALL_COMMAND INCLUDE_PATH=${INSTALL_ROOT}/include LIBRARY_PATH=${INSTALL_ROOT}/lib BINARY_PATH=${INSTALL_ROOT}/bin make install -f win32/Makefile.gcc SHARED_MODE=1
  )
endif()

# libiconv
ExternalProject_Get_Property(libiconv-download download_dir download_name)


if (DEFINED WIN32)
  ExternalProject_Add(libiconv-build2
    PREFIX builds/libiconv-build
    DEPENDS libiconv-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=be7d67e50d72ff067b2c0291311bc283add36965 
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT} 
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

# libxml2
ExternalProject_Get_Property(libxml2-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(libxml2-build
    PREFIX builds/libxml2-build
    DEPENDS libxml2-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=f46a37ea6d869f702e03f393c376760f3cbee673
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT} --without-python --with-zlib=${INSTALL_ROOT}
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

if (DEFINED WIN32)
  ExternalProject_Add(libxml2-build
    PREFIX builds/libxml2-build
    DEPENDS libxml2-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=f46a37ea6d869f702e03f393c376760f3cbee673
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT} --without-python --with-zlib=${INSTALL_ROOT}
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

# boost
ExternalProject_Get_Property(boost-download download_dir download_name)
set (BUILD_CMD_BASE ./bjam -j${JJ} variant=release --layout=tagged --with-math --with-program_options --with-random threading=multi)
set (INSTALL_CMD_BASE ./bjam -j${JJ} variant=release --layout=tagged --with-math --with-program_options --with-random threading=multi)
set (BUILD_CMD_X64 ${BUILD_CMD_BASE} stage)
set (INSTALL_CMD_X64 ${INSTALL_CMD_BASE} --prefix=${INSTALL_ROOT} install)

if (DEFINED UNIX)

  
endif()

if (DEFINED WIN32)
  ExternalProject_Add(boost-build
    PREFIX builds/boost-build
    DEPENDS boost-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=5123209db194d66d69a9cfa5af8ff473d5941d97
    # Using this trick https://stackoverflow.com/questions/5012429/building-boost-under-msys-cant-find-mingw-jam
    CONFIGURE_COMMAND ./bootstrap.sh --with-toolset=mingw COMMAND sed -i s/mingw/gcc/ project-config.jam
    BUILD_COMMAND ${BUILD_CMD_X64} 
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND ${INSTALL_CMD_X64}
  )
endif()

ExternalProject_Get_Property(mlpack-download download_dir download_name)
if (DEFINED UNIX)

  
endif()

if (DEFINED WIN32)
  ExternalProject_Add(mlpack-build
    PREFIX builds/mlpack-build
    DEPENDS mlpack-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=ad4909e4978edf03ff70d5f3d884efb24b5992a4
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${INSTALL_ROOT} -DCMAKE_PREFIX_PATH=${INSTALL_ROOT} -DDEBUG=OFF -DPROFILE=OFF
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()

# libpca
ExternalProject_Get_Property(libpca-download download_dir download_name)
if (DEFINED UNIX)
  ExternalProject_Add(libpca-build
    PREFIX builds/libpca-build
    DEPENDS libpca-download 
    URL ${download_dir}/${download_name}
    URL_HASH SHA1=ead870a2a2c6ca4b62c180d782a051ee476fa030
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ./configure --prefix=${INSTALL_ROOT} --with-armadillo-libdir=${INSTALL_ROOT}/lib --with-armadillo-incdir=${INSTALL_ROOT}/include
    BUILD_COMMAND make -j${JJ}
    INSTALL_COMMAND make install
  )
endif()




