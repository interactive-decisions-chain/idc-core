// Copyright (c) 2012-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2018-2019 The IDCC Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

/**
 * Functionality for communicating with IDCCGate.
 */
#ifndef BITCOIN_IDCCCONTROL_H
#define BITCOIN_IDCCCONTROL_H

#include <string>

#include <boost/function.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/thread.hpp>

extern const std::string DEFAULT_IDCC_CONTROL;
static const bool DEFAULT_LISTEN_ONION = true;

void StartIDCCControl(boost::thread_group& threadGroup);
void InterruptIDCCControl();
void StopIDCCControl();

#endif /* BITCOIN_IDCCCONTROL_H */
