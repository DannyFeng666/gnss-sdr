/*!
 * \file preamble_correlator_test.cc
 * \brief  This file implements tests for preamble detection.
 * \author Carles Fernandez-Prades, 2020. cfernandez(at)cttc.es
 *
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2019  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 * -------------------------------------------------------------------------
 */

#include "GPS_L1_CA.h"
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <numeric>
#include <random>
#include <vector>

TEST(PreambleCorrelationTest, TestMethods)
{
    int64_t n_iter = 100000;
    int32_t corr_value = 0;
    int32_t corr_value2 = 0;

    int32_t sum_corr1 = 0;
    int32_t sum_corr2 = 0;

    std::vector<float> d_symbol_history(GPS_CA_PREAMBLE_LENGTH_SYMBOLS, 0.0);
    std::array<int32_t, GPS_CA_PREAMBLE_LENGTH_BITS> d_preamble_samples{};

    std::chrono::time_point<std::chrono::system_clock> start, end, start2, end2;

    // fill the inputs
    std::random_device rd;
    std::default_random_engine e2(rd());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    std::generate(d_symbol_history.begin(), d_symbol_history.end(), [&dist, &e2]() { return dist(e2); });

    int32_t n = 0;
    for (int32_t i = 0; i < GPS_CA_PREAMBLE_LENGTH_BITS; i++)
        {
            if (GPS_CA_PREAMBLE[i] == '1')
                {
                    d_preamble_samples[n] = 1;
                    n++;
                }
            else
                {
                    d_preamble_samples[n] = -1;
                    n++;
                }
        }

    // Compute correlation, method 1
    start = std::chrono::system_clock::now();
    for (int64_t kk = 0; kk < n_iter; kk++)
        {
            corr_value = 0;
            for (int32_t i = 0; i < GPS_CA_PREAMBLE_LENGTH_BITS; i++)
                {
                    if (d_symbol_history[i] < 0.0)
                        {
                            corr_value -= d_preamble_samples[i];
                        }
                    else
                        {
                            corr_value += d_preamble_samples[i];
                        }
                }
            sum_corr1 += corr_value;
        }
    end = std::chrono::system_clock::now();

    // Compute correlation, method 2
    start2 = std::chrono::system_clock::now();
    for (int64_t kk = 0; kk < n_iter; kk++)
        {
            int32_t ii = -1;
            corr_value2 = std::accumulate(d_symbol_history.begin(),
                d_symbol_history.begin() + GPS_CA_PREAMBLE_LENGTH_BITS,
                0,
                [&ii, &d_preamble_samples](float a, float b) { return (b > 0.0 ? a + d_preamble_samples[++ii] : a - d_preamble_samples[++ii]); });
            sum_corr2 += corr_value2;
        }
    end2 = std::chrono::system_clock::now();

    EXPECT_EQ(corr_value, corr_value2);
    EXPECT_EQ(sum_corr1, sum_corr2);

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::chrono::duration<double> elapsed_seconds2 = end2 - start2;
    std::cout << "Correlation computed with 'C for': done in " << elapsed_seconds.count() * 1.0e9 / n_iter << " nanoseconds" << std::endl;
    std::cout << "Correlation computed with lambda:  done in " << elapsed_seconds2.count() * 1.0e9 / n_iter << " nanoseconds" << std::endl;
}
