spooky
======

SpookyHash V2 is a fast x64 targeted hash developed by Bob Jenkins. This
python library is a wrapper around Bob Jenkin's public domain c++
implementation (current as of August 2012).

In python2 results are all `long` type for consistency despite the fact that
32bit ints do not need to be.

The bit width features are a convenience to save a masking operation if you
need shorter hashes. There isn't a significant performance difference between
the hash size options as they are all computed internally as 128bit hashes.

Usage
-----

    >>> from spooky import hash128, hash64, hash32
    >>> s = 'this is only a test...'
    >>> hash128(s) #128bit python int from 2 unsigned long long ints in c
    94655121727368234505791352840874203973

    >>> hash64(s) #64bit int
    13961228348271205189

    >>> hash32(s) #32bit int
    2261883717

    >>> hash32(s) == hash64(s) & 0xffffffff == hash128(s) & 0xffffffff
    True

    >>> from binascii import hexlify #if you prefer hex strings to ints
    >>> hexlify(hash128(s).to_bytes(16, 'little'))
    b'459bd186363fc0c1f1da8d27d0e93547'
