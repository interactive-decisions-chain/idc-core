#FROM debian:stretch
FROM ubuntu:18.04
LABEL maintainer="The IDCC Core Developers <grogen@id-chain.org>"
LABEL description="Dockerised IDCC Core, built from Travis"

RUN apt-get update && apt-get install -y software-properties-common unzip
RUN apt-get install -y wget

RUN wget https://gitlab.com/ID-Chain/idc-core/tags/idcc-qt-linux-18.zip
RUN unzip idcc-qt-linux-18.zip
RUN cp idccd /usr/local/bin

VOLUME ["/opt/idcc"]

EXPOSE 9888
EXPOSE 9888
EXPOSE 9777
EXPOSE 9777

CMD ["idccd", "--conf=/opt/idcc/idcc.conf", "--printtoconsole"]
