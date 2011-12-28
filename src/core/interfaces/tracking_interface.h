/*!
 * \file tracking_interface.h
 * \brief This class represents an interface to a tracking block.
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *
 * Abstract class for tracking interfaces. Since all its methods are virtual,
 * this class cannot be instantiated directly, and a subclass can only be
 * instantiated directly if all inherited pure virtual methods have been
 * implemented by that class or a parent class.
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


#ifndef GNSS_SDR_TRACKING_INTERFACE_H_
#define GNSS_SDR_TRACKING_INTERFACE_H_

#include "gnss_block_interface.h"

template<typename Data>class concurrent_queue;

/*!
 * \brief This abstract class represents an interface to a tracking block.
 *
 * Abstract class for tracking interfaces. Since all its methods are virtual,
 * this class cannot be instantiated directly, and a subclass can only be
 * instantiated directly if all inherited pure virtual methods have been
 * implemented by that class or a parent class.
 *
 */
class TrackingInterface : public GNSSBlockInterface
{

public:

    virtual void start_tracking() = 0;
    virtual void set_satellite(unsigned int satellite) = 0;
    virtual void set_channel(unsigned int channel) = 0;
    virtual void set_prn_code_phase(signed int phase_samples) = 0;
    virtual void set_doppler_freq_shift(float doppler_freq_hz) = 0;
    virtual void set_acq_sample_stamp(unsigned long int sample_stamp) = 0;
    virtual void set_channel_queue(concurrent_queue<int> *channel_internal_queue) = 0;

};

#endif /* GNSS_SDR_TRACKING_INTERFACE_H_ */
