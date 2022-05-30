#!/bin/bash
cd ..
docker rmi -f s21_dec:1.0 &&
docker build . -t s21_dec:1.0 -f docker/Dockerfile &&
docker run s21_dec:1.0 
