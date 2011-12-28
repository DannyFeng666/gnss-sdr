/*!
 * \file gps_l1_ca_dll_pll_tracking.h
 * \brief  Interface of an adapter of a DLL+PLL tracking loop block
 * for GPS L1 C/A to a TrackingInterface
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *         Javier Arribas, 2011. jarribas(at)cttc.es
 *
 * Code DLL + carrier PLL according to the algorithms described in:
 * K.Borre, D.M.Akos, N.Bertelsen, P.Rinder, and S.H.Jensen,
 * A Software-Defined GPS and Galileo Receiver. A Single-Frequency
 * Approach, Birkha user, 2007
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2010-2011  (see AUTHORS file for a list of contributors)
 *
 * GNSS-SDR is a software defined Global Navigation
 *          Satellite Systems receiver
 *
 * This file is part of GNSS-SDR.
 *
 * GNSS-SDR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * GNSS-SDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNSS-SDR. If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef GNSS_SDR_GPS_L1_CA_DLL_PLL_TRACKING_H_
#define GNSS_SDR_GPS_L1_CA_DLL_PLL_TRACKING_H_

#include "tracking_interface.h"
#include "gps_l1_ca_dll_pll_tracking_cc.h"
#include <gnuradio/gr_msg_queue.h>

class ConfigurationInterface;

/*!
 * \brief This class implements a code DLL + carrier PLL tracking loop
 */
class GpsL1CaDllPllTracking : public TrackingInterface
{

public:

  GpsL1CaDllPllTracking(ConfigurationInterface* configuration,
            std::string role,
            unsigned int in_streams,
            unsigned int out_streams,
            gr_msg_queue_sptr queue);

    virtual ~GpsL1CaDllPllTracking();

    std::string role()
    {
        return role_;
    }
    std::string implementation()
    {
        return "tracking";
    }
    size_t item_size()
    {
        return item_size_;
    }

    void connect(gr_top_block_sptr top_block);
    void disconnect(gr_top_block_sptr top_block);
    gr_basic_block_sptr get_left_block();
    gr_basic_block_sptr get_right_block();

    /*!
     * \brief Set satellite ID
     */
    void set_satellite(unsigned int satellite);

    /*!
     * \brief Set tracking channel unique ID
     */
    void set_channel(unsigned int channel);

    /*!
     * \brief Set acquisition code phase in samples
     */
    void set_prn_code_phase(signed int phase_samples);

    /*!
     * \brief Set acquisition Doppler frequency in Hz.
     */
    void set_doppler_freq_shift(float doppler_freq_hz);

    /*!
     * \brief Set tracking channel internal queue
     */
    void set_channel_queue(concurrent_queue<int> *channel_internal_queue);

    void start_tracking();

    /*!
     * \brief Set acquisition sample stamp in samples, in order to detect
     * the delay between acquisition and tracking
     */
    void set_acq_sample_stamp(unsigned long int sample_stamp);

private:

    gps_l1_ca_dll_pll_tracking_cc_sptr tracking_;
    size_t item_size_;

    unsigned int satellite_;
    unsigned int channel_;

    std::string role_;
    unsigned int in_streams_;
    unsigned int out_streams_;
    gr_msg_queue_sptr queue_;
    concurrent_queue<int> *channel_internal_queue_;
};

#endif // GNSS_SDR_GPS_L1_CA_DLL_PLL_TRACKING_H_
