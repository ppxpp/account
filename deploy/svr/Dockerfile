FROM ubuntu:16.04
MAINTAINER zhouhao3207@163.com
ADD . /account
WORKDIR /account
EXPOSE 50051
ENV LD_LIBRARY_PATH /account/lib
RUN pwd
CMD ./server