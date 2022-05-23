FROM alpine:3.14

RUN apk --no-cache --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
	build-base \
    python3 \
    pip3 \
    valgrind \
    cppcheck \
	alpine-sdk \
	pcre-dev

RUN mkdir /s21_string

COPY . /s21_string

WORKDIR "/s21_string"
