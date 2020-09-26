FROM ubuntu:bionic

RUN apt-get update &&
    apt-get install -y g++-7 cmake crossbuild-essential-armhf crossbuild-essential-arm64