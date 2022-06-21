FROM ubuntu:18.04 as env

RUN groupdel dialout

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    gdb \
    libssl-dev \
    zlib1g-dev \
    dos2unix \
    rsync \
    doxygen \
    graphviz \
    libc6-dbg \
    valgrind \
    git \
    libopencv-dev \
    libomp-dev \
    cmake \
    libsqlite3-dev\
    wget

ARG USER_ID
ARG GROUP_ID
ARG DEP_DIR
ARG SRC_DIR

ENV DEP_DIR=/${DEP_DIR}
RUN echo ${DEP_DIR}
ENV SRC_DIR=/${SRC_DIR}
RUN echo ${SRC_DIR}


RUN addgroup --gid $GROUP_ID user
RUN adduser --disabled-password --gecos '' --uid $USER_ID --gid $GROUP_ID user

RUN mkdir -p ${SRC_DIR}
RUN mkdir -p ${DEP_DIR}
WORKDIR ${SRC_DIR}
RUN mkdir imageio
WORKDIR ${SRC_DIR}/imageio
RUN wget https://github.com/fiveman1/imageio/raw/master/imageio.tar.gz
RUN tar xzvf imageio.tar.gz
RUN cp -R include ${DEP_DIR}
RUN mkdir ${DEP_DIR}/lib
RUN mv lib/libimageio-docker.so lib/libimageio.so
RUN cp lib/libimageio.so ${DEP_DIR}/lib

WORKDIR ${SRC_DIR}
RUN git clone https://github.com/dtorban/CppWebServer.git CppWebServer
RUN mkdir -p ${SRC_DIR}/CppWebServer/build
RUN git clone https://github.com/google/googletest.git gtest
RUN mkdir -p ${SRC_DIR}/gtest/build
WORKDIR ${SRC_DIR}/CppWebServer/build
RUN cmake -DCMAKE_INSTALL_PREFIX=${DEP_DIR} ..
RUN make install -j
WORKDIR ${SRC_DIR}/gtest/build
RUN cmake -DCMAKE_INSTALL_PREFIX=${DEP_DIR} ..
RUN make install -j

RUN echo OPENCV_INCLUDES=`pkg-config --cflags opencv` >> ${DEP_DIR}/env
RUN echo OPENCV_LIBS=`pkg-config --libs opencv` >> ${DEP_DIR}/env

RUN find ${DEP_DIR} -type d -exec chmod 775 {} \;
RUN find ${DEP_DIR} -type f -exec chmod 664 {} \;

RUN mkdir -p /home/user
WORKDIR /home/user/repo

USER user
