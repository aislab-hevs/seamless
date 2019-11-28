FROM node:12

# Install libboost for the simulator

RUN cd /opt && wget https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.tar.bz2 \
    && tar --bzip2 -xf boost_1_65_1.tar.bz2 \
    && rm boost_1_65_1.tar.bz2 \
    && cd boost_1_65_1 \
    && ./bootstrap.sh --with-libraries=filesystem   \
    && ./b2 --prefix=/usr install

# Install pre-requisites for omnet++

RUN apt update && apt install -y build-essential gcc g++ bison flex perl \
    python python3 qt5-default libqt5opengl5-dev tcl-dev tk-dev \
    libxml2-dev zlib1g-dev default-jre doxygen graphviz libwebkitgtk-1.0

# Install omnet++ framework

RUN cd /opt &&  wget https://github.com/omnetpp/omnetpp/releases/download/omnetpp-5.5.1/omnetpp-5.5.1-src-linux.tgz \
    && tar xvzf omnetpp-5.5.1-src-linux.tgz \
    && rm omnetpp-5.5.1-src-linux.tgz 

ENV PATH=/opt/omnetpp-5.5.1/bin:$PATH

RUN cd /opt/omnetpp-5.5.1 \
    && ./configure WITH_OSG=no WITH_OSGEARTH=no && make 
   
WORKDIR /usr/src/backend

COPY ./ ./

RUN npm install

# Compile simulator

RUN cd simulator/agent_gprt && make

CMD ["/bin/bash"]