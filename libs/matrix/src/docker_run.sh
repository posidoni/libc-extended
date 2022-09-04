#!/bin/bash
docker rmi -f alpine:3.14 && docker build . -t alpine:3.14 -f materials/build/Dockerfile && docker run alpine:3.14