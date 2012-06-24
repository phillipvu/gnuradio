/* -*- c++ -*- */
/*
 * Copyright 2008,2010,2012 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <digital_descrambler_bb.h>
#include <gr_io_signature.h>

digital_descrambler_bb_sptr
digital_make_descrambler_bb(int mask, int seed, int len)
{
  return gnuradio::get_initial_sptr(new digital_descrambler_bb(mask, seed, len));
}

digital_descrambler_bb::digital_descrambler_bb(int mask, int seed, int len)
  : gr_sync_block("descrambler_bb",
		  gr_make_io_signature (1, 1, sizeof (unsigned char)),
		  gr_make_io_signature (1, 1, sizeof (unsigned char))),
    d_lfsr(mask, seed, len)
{
}

int
digital_descrambler_bb::work(int noutput_items,
			     gr_vector_const_void_star &input_items,
			     gr_vector_void_star &output_items)
{
  const unsigned char *in = (const unsigned char *) input_items[0];
  unsigned char *out = (unsigned char *) output_items[0];

  for (int i = 0; i < noutput_items; i++)
    out[i] = d_lfsr.next_bit_descramble(in[i]);

  return noutput_items;
}
