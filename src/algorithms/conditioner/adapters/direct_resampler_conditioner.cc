/*!
 * \file direct_resampler_conditioner.cc
 * \brief Brief description of the file here
 * \author Carlos Aviles, 2010. carlos.avilesr(at)googlemail.com
 *
 * Detailed description of the file here if needed.
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

#include "direct_resampler_conditioner.h"

// #include <gnuradio/usrp_source_c.h>
#include <gnuradio/gr_file_sink.h>

#include "direct_resampler_conditioner_cc.h"
#include "direct_resampler_conditioner_ss.h"

#include "configuration_interface.h"

#include <glog/log_severity.h>
#include <glog/logging.h>

using google::LogMessage;

DirectResamplerConditioner::DirectResamplerConditioner(
        ConfigurationInterface* configuration, std::string role,
        unsigned int in_stream, unsigned int out_stream) :
    role_(role), in_stream_(in_stream), out_stream_(out_stream)
{

    std::string default_item_type = "short";
    std::string default_dump_file = "./data/signal_conditioner.dat";

    sample_freq_in_ = configuration->property(role_ + ".sample_freq_in",
            (double)4000000.0);
    sample_freq_out_ = configuration->property(role_ + ".sample_freq_out",
            (double)2048000.0);
    item_type_ = configuration->property(role + ".item_type",
            default_item_type);
    dump_ = configuration->property(role + ".dump", false);
    dump_filename_ = configuration->property(role + ".dump_filename",
            default_dump_file);

    if (item_type_.compare("gr_complex") == 0)
    {
        item_size_ = sizeof(gr_complex);
        resampler_ = direct_resampler_make_conditioner_cc(sample_freq_in_,
                sample_freq_out_);
    }
    else if (item_type_.compare("short") == 0)
    {
        item_size_ = sizeof(short);
        resampler_ = direct_resampler_make_conditioner_ss(sample_freq_in_,
                sample_freq_out_);
    }
    else
    {
        LOG_AT_LEVEL(WARNING) << item_type_
                << " unrecognized item type. Using short";
        item_size_ = sizeof(short);
    }

    if (dump_)
    {
        DLOG(INFO) << "Dumping output into file " << dump_filename_;
        file_sink_ = gr_make_file_sink(item_size_, dump_filename_.c_str());
    }

    DLOG(INFO) << "sample_freq_in " << sample_freq_in_;
    DLOG(INFO) << "sample_freq_out" << sample_freq_out_;
    DLOG(INFO) << "Item size " << item_size_;
    DLOG(INFO) << "resampler(" << resampler_->unique_id() << ")";
    if (dump_)
    {
        DLOG(INFO) << "file_sink(" << file_sink_->unique_id() << ")";
    }
}
DirectResamplerConditioner::~DirectResamplerConditioner()
{
}

void DirectResamplerConditioner::connect(gr_top_block_sptr top_block)
{

    if (dump_)
    {
        top_block->connect(resampler_, 0, file_sink_, 0);
        DLOG(INFO) << "connected resampler to file sink";
    }
    else
    {
        DLOG(INFO) << "nothing to connect internally";
    }

}

void DirectResamplerConditioner::disconnect(gr_top_block_sptr top_block)
{
    if (dump_)
    {
        top_block->disconnect(resampler_, 0, file_sink_, 0);
    }
}

gr_basic_block_sptr DirectResamplerConditioner::get_left_block()
{
    return resampler_;
}

gr_basic_block_sptr DirectResamplerConditioner::get_right_block()
{
    return resampler_;
}
