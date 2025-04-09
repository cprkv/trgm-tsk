FROM gcc:4

# install valgrind
RUN echo "deb http://archive.debian.org/debian/ jessie main contrib non-free" > /etc/apt/sources.list \
      && apt update \
      && apt install -y --force-yes valgrind

# install cmake
RUN wget https://cmake.org/files/v3.1/cmake-3.1.0-Linux-x86_64.sh -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh

ENV PATH="/usr/bin/cmake/bin:${PATH}"
