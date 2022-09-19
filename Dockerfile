FROM ubuntu:latest

MAINTAINER xingzheng "3024979463@qq.com"

RUN  sed -i s@/archive.ubuntu.com/@/mirrors.aliyun.com/@g /etc/apt/sources.list
RUN  apt-get clean

WORKDIR /root
RUN mkdir -p /root/xv6

RUN apt-get update && apt-get install git build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu -y

EXPOSE 22

CMD /bin/bash