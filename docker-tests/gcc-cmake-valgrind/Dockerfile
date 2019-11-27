FROM gcc:4

RUN wget https://github.com/Kitware/CMake/releases/download/v3.1.0/cmake-3.1.0-Linux-x86_64.sh \
      -q -O /tmp/cmake-install.sh \
      && chmod u+x /tmp/cmake-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/cmake-install.sh

RUN apt-get update && apt-get install -y valgrind

ENV PATH="/usr/bin/cmake/bin:${PATH}"
