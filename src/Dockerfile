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

RUN mkdir /s21_matrix

COPY . /s21_matrix

WORKDIR "/s21_matrix"

RUN make


CMD ["/bin/bash"]