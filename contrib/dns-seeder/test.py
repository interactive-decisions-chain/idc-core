import socket

seeders = [
    'dseed1.id-chain.org',
    'dseed2.id-chain.org',
    'dseed3.id-chain.org',
    'dseed4.id-chain.org',
    'dseed5.id-chain.org',
    'dseed6.id-chain.org'
]

for seeder in seeders:
    try:
        ais = socket.getaddrinfo(seeder, 0)
    except socket.gaierror:
        ais = []
    
    # Prevent duplicates, need to update to check
    # for ports, can have multiple nodes on 1 ip.
    addrs = []
    for a in ais:
        addr = a[4][0]
        if addrs.count(addr) == 0:
            addrs.append(addr)
    
    print(seeder + ' = ' + str(len(addrs)))
