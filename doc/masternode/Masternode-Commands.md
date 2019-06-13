# Masternode Commands

`systemctl start idchaind`
\- Starts the IDChain Daemon

`systemctl stop idchaind`
\- Stops the IDChain Daemon

`systemctl restart idchaind`
\- Restarts the IDChain Daemon

`systemctl status idchaind`
\- Displays the status of the IDChain Daemon

`idchain-cli masternode status`
\- Displays the status of the IDChain masternode running on the VPS

`idchain-cli getinfo`
\- Displays general info about the masternode

`idchain-cli masternodecurrent`
\- Displays additional info about the masternode

`ps aux | grep idchain`
\- Shows if the idchaind process is running

`dmesg | egrep -i 'killed process'`
\- Lets you know whether idchaind was killed due to lack of memory

`nano ~/.idchain/idchain.conf`
\- Edits your idchain.conf file

`killall -9 idchaind`
\- Force quits idchaind (*USE WITH CAUTION*)

`idchain-cli getpeerinfo | grep synced_headers`
\- Displays synced headers

`idchain-cli getmasternodecount`
\- Displays count of all masternodes

`bash <( curl https://raw.githubusercontent.com/idchain-crypto/IDChain-MN-Install/master/refresh_node.sh )`

Refreshes your node by clearing the chaindata

`bash <( curl https://raw.githubusercontent.com/idchain-crypto/IDChain-MN-Install/master/update_node.sh )`

Updates your node to the newest version
