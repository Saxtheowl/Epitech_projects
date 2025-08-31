#
# EPITECH PROJECT, 2025
# Popeye - CI container
#
FROM ubuntu:22.04

RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential make gcc git \
    pkg-config \
    libcriterion-dev gcovr \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

CMD ["/bin/sh"]

