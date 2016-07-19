#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os
from PIL import Image


def slice_pic(src_file, slice_w, slice_h):
    base_dir = os.path.dirname(os.path.abspath(src_file))
    base_name = os.path.splitext(os.path.basename(src_file))[0]
    src_image = Image.open(src_file)
    src_w = src_image.size[0]
    src_h = src_image.size[1]
    cols = src_w / slice_w
    rows = src_h / slice_h
    for col in range(cols):
        for row in range(rows):
            x = col * slice_w
            y = row * slice_h
            mx = min(x + slice_w, src_w)
            my = min(y + slice_h, src_h)
            tile = Image.new('RGBA', [slice_w, slice_h])
            tile.paste(src_image.crop((x, y, mx, my)), (0, 0))
            dst_file = os.path.join(base_dir, "%s-%d-%d.png" % (base_name, col, row))
            tile.save(dst_file)


if __name__ == '__main__':
    slice_pic(sys.argv[1], 64, 64)
