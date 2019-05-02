Quick Docker image for idccd
---------------------------

Build docker image:

    docker/build.sh

Push docker image:

    docker/push.sh

Pull idcccore/idcc:latest from docker hub  at [idcc-dockerhub](https://hub.docker.com/r/idcccore/idcc)

    sudo docker pull idcccore/idcc

Run docker image

    sudo docker run idcccore/idcc

Build docker for idccd
----------
A Docker configuration with idccd node by default.

    sudo apt install apt-transport-https ca-certificates curl software-properties-common; curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -; sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"; sudo apt-get update; sudo apt install docker-ce   
---------------------------------------------------        

    mkdir idcc-mounted-data
    docker run --name idcc -d \
     --env 'IDCC_RPCUSER=rpciser' \
     --env 'IDCC_RPCPASSWORD=rpcpassword' \
     --env 'IDCC_TXINDEX=1' \
     --volume ~/idcc-mounted-data:~/.idcc \
     -p 9888:9888 \
     --publish 9888:9888 \
     idcccore/idcc
----------------------------------------------------
Logs

    docker logs -f idcc

----------------------------------------------------

## Configuration

Set your `idcc.conf` file can be placed in the `idcc-mounted data` dir.
Otherwise, a default `idcc.conf` file will be automatically generated based
on environment variables passed to the container:

| name | default |
| ---- | ------- |
| BTC_RPCUSER | rpcuser |
| BTC_RPCPASSWORD | rpcpassword |
| BTC_RPCPORT | 9888 |
| BTC_RPCALLOWIP | ::/0 |
| BTC_RPCCLIENTTIMEOUT | 30 |
| BTC_DISABLEWALLET | 1 |
| BTC_TXINDEX | 0 |
| BTC_TESTNET | 0 |
| BTC_DBCACHE | 0 |
| BTC_ZMQPUBHASHTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBHASHBLOCK | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWBLOCK | tcp://0.0.0.0:28333 |


## Daemonizing

If you're daemonizing is to use Docker's
[Daemonizing](https://docs.docker.com/config/containers/start-containers-automatically/#use-a-restart-policy),
but if you're insistent on using systemd, you could do something like

```
$ cat /etc/systemd/system/idccd.service

# idccd.service #######################################################################
[Unit]
Description=IDCC
After=docker.service
Requires=docker.service

[Service]
ExecStartPre=-/usr/bin/docker kill idcc
ExecStartPre=-/usr/bin/docker rm idcc
ExecStartPre=/usr/bin/docker pull idcccore/idcc
ExecStart=/usr/bin/docker run \
    --name idcc \
    -p 9888:9888 \
    -p 9888:9888 \
    -v /data/idccd:/root/.idcc \
    idcccore/idcc
ExecStop=/usr/bin/docker stop idcc
```
