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

RUN mkdir /s21_math

COPY . /s21_math

WORKDIR "/s21_math"

RUN make

CMD ["/bin/bash"]