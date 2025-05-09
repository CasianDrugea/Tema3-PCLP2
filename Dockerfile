FROM ghcr.io/open-education-hub/vmcheker-next-base-image/base-container:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -yqq && \
    apt-get install -yqq gcc-multilib nasm bc qemu-user gdb && \
    apt-get install -y build-essential valgrind

COPY ./checker ${CHECKER_DATA_DIRECTORY}
