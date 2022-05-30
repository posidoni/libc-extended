FROM alpine:3.14

RUN apk --no-cache --upgrade add \
    git \
    git-lfs \
    curl \
    jq \
    bash \
	build-base \
    python3 \
    valgrind \
    cppcheck \
	alpine-sdk \
	pcre-dev \
    clang \
    bash \
    check-dev

RUN mkdir /s21_decimal

COPY . /s21_decimal

WORKDIR "/s21_decimal"

RUN "chmod +x docker/test_s21_decimal"

ENTRYPOINT ["/bin/bash","docker/test_s21_decimal.sh"]

