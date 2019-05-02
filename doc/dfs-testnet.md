![IDCC Logo](../src/qt/res/images/idcc_logo_horizontal.png)

"FIRST OF ITS KIND"

IDCCcore is GNU AGPLv3 licensed.


[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2F216k155%2Fidcc.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2F216k155%2Fidcc?ref=badge_shield) [![Build Status](https://travis-ci.org/IDCC-Core/idcc.svg?branch=master)](https://travis-ci.org/IDCC-Core/idcc) [![GitHub version](https://badge.fury.io/gh/IDCC-Core%2Fidcc.png)](https://badge.fury.io/gh/IDCC-Core%2Fidcc.png) [![HitCount](http://hits.dwyl.io/216k155/idcc.svg)](http://hits.dwyl.io/216k155/idcc)
<a href="https://discord.gg/A6YW6uh"><img src="https://discordapp.com/api/guilds/364500397999652866/embed.png" alt="Discord server" /></a> <a href="https://twitter.com/intent/follow?screen_name=IDCC_COIN"><img src="https://img.shields.io/twitter/follow/IDCC_COIN.svg?style=social&logo=twitter" alt="follow on Twitter"></a>
                                                                                                                                                     
[Website](https://idcccore.io) — [IDCCtre + IDCCGate](https://github.com/IDCC-Core/idcctre) - [PoS Web Wallet](https://idcc.poswallet.io) — [Block Explorer](https://explorer.idcccore.io/) — [Blog](https://reddit.com/r/IDCCCoin) — [Forum](https://bitcointalk.org/index.php?topic=2254046.0) — [Telegram](https://t.me/IDCCcoinOfficialChat) — [Twitter](https://twitter.com/IDCC_Coin)

Technical description of the Distributed File System (Testnet)
=================================

RPC Command parameters can be found in `help`.

Example:

    idcc/src/idcc-cli -testnet=1 -rpcpassword=123456 help dfsannounce

List of `RPC commands`:

| RPC Commands | Function |
|:-----------|:-----------|
| dfsannounce | Add file to dfs |
| dfscancelorder | Cancel request |
| dfsgetinfo | GetDFSInfo |
| dfssetparams | Setting storage parameters `[for pmn]` (price, frequency of evidence) |
| dfssetfolder & dfssettempfolder | Select storage and temporary storage `[for pmn]` |
| dfsremoveoldorders | Delete old queries |
| dfslistorders | List of orders | 
| dfslistproposals | List of proposals |
| dfsacceptproposal | Selection of offer for order |
| dfslocalstorage | List of local files |
| dfsdecrypt | Decrypt file |

---------------------------------------------------------------------

* servers 

        45.32.245.24 (root@45.32.245.24 pass: please contact dev)
    
        66.42.51.223 (root@66.42.51.223 pass: please contact dev)
         
Both servers are equivalent and can act as "Alice" and "Bob" when requested to save the file (from one of them you can send a request to save the file to another).

* Demons are used in general testnet, with the key 

         --datadir =" / root / idcctestnet / "

To execute any rpc command on these servers you should specify the `testnet` and `rpcpassword = 123456` keys.

Example: 

        idcc / src / idcc-cli -testnet = 1 -rpcpassword = 123456 dfsgetinfo

As a result, you should see:

        {
        "enabled": true,
        "myip": "45.32.245.24:28333",
         "dfsfolder": "/root/idcctestnet/testnet4/dfs",
         "dfstempfolder": "/root/idcctestnet/testnet4/dfstemp",
         "rate": 1,
         "maxblocksgap": 100
        }

To send a file you need to make an rpc call `dfsannounce`:

        idcc/src/idcc-cli -testnet=1 -rpcpassword=123456 dfsannounce "/root/file.test" 100 200

Where `/root/file.test` is the path to the file you want to save, `100` is the maximum file storage cost, measured in `1Kb * 1sec / 0.00000001 idcc`, and `200` is the maximum number of blocks, the allowable intervals between transactions containing evidence of file storage.

The function should return a unique hash order like the example below:

    f37996a118cc14e16a300503ef23062f6711721ebcce1ed9df91680cdeee0c40

Then you need to wait a little more than `1 minute`, during this time all dfs nodes connected to the network (at least the 2nd server) will send their proposal to this order.

You can view a list of all proposals for this order with the command: 
        
    dfslistproposals <order hash> 
    
Example:
 
    idcc/src/idcc-cli -testnet=1 -rpcpassword=123456 dfslistproposals f37996a118cc14e16a300503ef23062f6711721ebcce1ed9df91680cdeee0c40 

There should be such an array of objects:
    
    [
        {
            "orderhash": "f37996a118cc14e16a300503ef23062f6711721ebcce1ed9df91680cdeee0c40",
            "proposalhash": "7a0bfcff85874200a180476211a2edf01eee1d9a6a43cb20e0652e94977c3040",
            "time": "1548331925",
            "address": "66.42.51.223:28333",
            "rate": 4
        }
    ]

Then (within a minute) an object with the minimum parameter `"rate"` will be automatically selected among all requests and a crypto-replica source file (encrypted with AES and RSA algorithms) will be created for it and transmitted to the specified address. If it turns out that this address has a "fake IP", then the actual file transfer will not occur. However, both hetzners haven't this problem, so the transfer must end in a regular way.

If everything all good, the other server should appear entry in `dfslocalstorage` in the `storage chunk` section. 

Moreover, You can check it with corresponding command below: 

    idcc/src/idcc-cli -testnet=1 -rpcpassword=123456 dfslocalstorage

You should see:

    [
     {
       "index": 0,
       "type": "storage chunk",
       "path": "/root/idcctestnet/testnet4/dfs",
       "totalSpace": "107374182400",
       "freeSpace": "107374114688",
       "files": [{
       "filename": "/root/idcctestnet/testnet4/dfs/667cb29cf32f3bb48d875d33e2b61d16996b606d0f42acdd6b254ba1ce3cd8ac_1548331987.idccfs",
       "uri": "667cb29cf32f3bb48d875d33e2b61d16996b606d0f42acdd6b254ba1ce3cd8ac",
       "size": "67712" }]
     }, 
     
     {
       "index": 0,
       "type": "temp chunk",
       "path": "/root/idcctestnet/testnet4/dfstemp",
       "totalSpace": "107374182400",
       "freeSpace": "107374182400",
       "files": []
     }
    ]

Also, the actual availability of this file and its size can be inspected using the usual bash tools at the address specified in the filename section (in this case `"filename"`):

    "/root/idcctestnet/testnet4/dfs/667cb29cf32f3bb48d875d33e2b61d16996b606d0f42acdd6b254ba1ce3cd8ac_1548331987.idccfs")

The file will be encrypted and have a size: the original file size is `126` divided, rounded up, multiplied by `128`.

You can decrypt it by running the command `dfsdecrypt`. 

Example:

    idcc/src/idcc-cli -testnet=1 -rpcpassword=123456 dfsdecrypt "f37996a118cc14e16a300503ef23062f6711721ebcce1ed9df91680cdeee0c40" "/root/file.test"

Then you can look at the contents of the file `/root/file.test` and compare it with the one that was on another vps.

For example on one server was:

    md5sum ~/file.test 

    f17211fa8630cadc9851894b74034948  /root/file.test

On the second server decrypted:

    md5sum ~/test
    
    f17211fa8630cadc9851894b74034948  /root/test

As you can see the hash sums of files are the same.

