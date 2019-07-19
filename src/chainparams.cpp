// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018-2019 The IDChain developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count) {
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0x000004ea898d3118b36547cbc2c779e635bca5ff5951f41788ae4495f4c55c4b"))
    (17500, uint256("00000000000229b6af9e428eb0ba72fcda7ed2510c90e5ac6d60ba820ef46ff3"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1562757410,// * UNIX timestamp of last checkpoint block
    19137,    // * total number of transactions between genesis and last checkpoint
    //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    250
};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100
};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const {
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams {
  public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x08;
        pchMessageStart[1] = 0x02;
        pchMessageStart[2] = 0x02;
        pchMessageStart[3] = 0x17;
        vAlertPubKey = ParseHex("0401bc08286a041282d437d68af86416aefc9018e7ff93bd9dd2d53b087332c134ba24d177ebafd9bff227df14554d687c73448b4d5e02f09e7dff25aede613795");
        nDefaultPort = 31569;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // IDChain starting difficulty is 1 / 2^12
        nMaxReorganizationDepth = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 120; // IDChain: 2 minutes
        nTargetSpacingSlowLaunch = 10 * 60;  // IDChain: 10 minutes (Slow launch - Block 2000)
        nTargetSpacing = 1 * 120; // IDChain: 2min after block 300
        nLastPOWBlock = 144840;
        nLastPOWBlockOld = 144840; // 1 year
        nLastSeeSawBlock = 155000; // last block for seesaw rewards
        nRampToBlock = 2000; // Slow start, ramp linearly to this block
        nMaturity = 60; // 120 Minutes
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 1;
        nMaxMoneyOut = 21525720 * COIN; // Year 2

        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "June 14, 2019 - IDChain - Open your mind for future! - Grogen";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 50 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04cc75ad0835baac499a7a523b19cb5ba118a188f1ce45dc1ba44166af1fa6ee79508d271da844b3a5c867191b420fcfcaac735ffb9e42be120926e3cea53bb4b4") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1560535200;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();;
        genesis.nNonce = 886283;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000004ea898d3118b36547cbc2c779e635bca5ff5951f41788ae4495f4c55c4b"));
        assert(genesis.hashMerkleRoot == uint256("0x5211f71c2ca7aa346866628505e23b0c2ca14885f62394f26eeb8dca92187a47"));

        vSeeds.push_back(CDNSSeedData("dseed1.id-chain.org", "dseed1.id-chain.org"));      // France (ONLINE.net)
        vSeeds.push_back(CDNSSeedData("dseed2.id-chain.org", "dseed2.id-chain.org"));      // France (ONLINE.net)
        vSeeds.push_back(CDNSSeedData("dseed3.id-chain.org", "dseed3.id-chain.org")); 	   // Germany (VULTR)
        vSeeds.push_back(CDNSSeedData("dseed4.id-chain.org", "dseed4.id-chain.org"));      // USA Silicon Valley (VULTR)
        vSeeds.push_back(CDNSSeedData("dseed5.id-chain.org", "dseed5.id-chain.org"));      // Australia (VULTR)
        vSeeds.push_back(CDNSSeedData("dseed6.id-chain.org", "dseed6.id-chain.org"));      // Singapore (VULTR)
        vSeeds.push_back(CDNSSeedData("dseed7.id-chain.org", "dseed7.id-chain.org"));      // Russia (Dedibox)
        vSeeds.push_back(CDNSSeedData("dseed8.id-chain.org", "dseed8.id-chain.org"));      // Canada (DigitalOcean)
        vSeeds.push_back(CDNSSeedData("dseed9.id-chain.org", "dseed9.id-chain.org"));      // Bangalore (DigitalOcean)

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 30); // D
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 128);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x77).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "0473edaedf047254715d9f952304f33e8b2fbe7381d5db3777016855ad8f99e87ef1da6c77536fd9eec3295289625858bf0a713cd6f2ac2c2d793c2800f23e91fa";
        strObfuscationPoolDummyAddress = "DPZnt71Ph1uwHDDu96ekpHSjNusr592foP";
        nStartMasternodePayments = 1560794400; //Mon, 17 June 2019 22:00:00 GMT

        /** Zerocoin */
        zerocoinModulus = "b2275261dcaa303374af30576c5f676c8c2f1596aae7814f932f08839d442a5b2f7eaac75ffe9481321cbaae1c48703eff"
                          "384222885cf9e07e3996fa36d25f0866a7f3834c2457b253b0bbbd0ec23036fcc6c84886cce4d6bcc917ce7fb40d3ffcc12984db02e55e4e"
                          "ccd205f7a239fe48ab27ea1124efa0a545ae434876b0b934ebcc54b03375c78bdbb1cde74c8e42048839e191f3986436f757c11d36b60942"
                          "f6b88f40acbcd4b36d82890e05b6e508192873dee5be51352e7215fbca7dfe30daac0efd8435426313557b1d193be3fa3be8c3c81f5501e0"
                          "52478afcfc1bd1f06ff429ecae3b682faa26bda5bb530fe1eca4d630fadc3b5d15e3d1feeeb161812894d3f17f497bb321c224f5419e30d2"
                          "b79511979fa41d24bc78c0aa18e12dc668b164841ce56bc8de5b7386cff2bb314b11094a4ad5661a7fd7b517181f8a999e61ddadc6936262"
                          "80b2692bc5b62bd328eb0b4c7d48b98942b0e6037add6568897f41adb825482057ae6224531047eef0cfd8f5510eb64e0610d83a1c7181";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee

        /** Staking Requirements */
        nStakeMinStartProtocol = 70855; // Starting protocol version (ActiveProtocol())
        nStakeMinConfirmations = 300; // Required number of confirmations
        nStakeMinAmount = 100 * COIN; // Minimum required staking amount
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
  public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0xd9;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xa0;

        vAlertPubKey = ParseHex("04753104b0eaa118d59b1a5b1d069431a7f7203bb9ad5c5d98aa953df962746f6ecef3a3273c77d410f7eb46eb1fd777222a9f3999657206a0631d5ae85f178a80");
        nDefaultPort = 25838;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 30; // 30 Seconds
        nTargetSpacing = 1 * 30;  // 30 Seconds
        nTargetSpacingSlowLaunch = 1 * 30; //

        nLastPOWBlock = 200;
        nLastPOWBlockOld = 500;
        nLastSeeSawBlock = 200;
        nMaturity = 15;
        nMaxMoneyOut = 33284220 * COIN; // 2032 Maximum
        nRampToBlock = 100;

        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1560535201;
        genesis.nNonce = 1025783;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x000006d9daa2d69c9882b17d9887db68fae02c3dffd0d24549e3361df25e5927"));
        assert(genesis.hashMerkleRoot == uint256("0x5211f71c2ca7aa346866628505e23b0c2ca14885f62394f26eeb8dca92187a47"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("tseed1.id-chain.org", "tseed1.id-chain.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 73); // Testnet idchain addresses start with 'W'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 12);  // Testnet idchain script addresses start with '5' or '6'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet idchain BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet idchain BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet idchain BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();
        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04f3b65bf13d74034529fba1a7005210bbe462e95ffcd88a2777de012111301db7deba4657ac1bb46654a074228e1599f3d5ffafca7b1884bb007f47e1712ddab8";
        strObfuscationPoolDummyAddress = "WZFzPKaweSADXHGdXE5YCEX2wNPBoQNRAY";
        nStartMasternodePayments = 1560794401; //Mon, 17 June 2019 22:00:01 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
        // here because we only have a 8 block finalization window on testnet

        /** Staking Requirements */
        nStakeMinStartProtocol = 70850; // Starting protocol version (ActiveProtocol())
        nStakeMinConfirmations = 30; // Required number of confirmations
        nStakeMinAmount = 500 * COIN; // Minimum required staking amount
    }
    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
  public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xa1;
        pchMessageStart[1] = 0xcf;
        pchMessageStart[2] = 0x7e;
        pchMessageStart[3] = 0xac;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // IDChain: 1 day
        nTargetSpacing = 1 * 60;        // IDChain: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1454124731;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 51476;
//        assert(hashGenesisBlock == uint256("0x4f023a2120d9127b21bbad01724fdb79b519f593f2a85b60d3d79160ec5f29df"));
        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
  public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) {
        fDefaultConsistencyChecks = afDefaultConsistencyChecks;
    }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {
        fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks;
    }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) {
        fSkipProofOfWorkCheck = afSkipProofOfWorkCheck;
    }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) {
        nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority;
    }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) {
        nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority;
    }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) {
        nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority;
    }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams() {
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network) {
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine() {
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
