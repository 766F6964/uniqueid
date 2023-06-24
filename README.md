# uniqueid

## Overview

This is a simple module that computes a unique system identifier, that remains unchanged after rebooting.
To achieve this, a combination of hardware and software attributes are combined.

## Why?

This module was created because there was no good inbuilt option available, to uniquely identify a (linux) system.
I wanted a unique identifier, that an application can use to know, if it is running on the same system.
Similar approaches like `/etc/machine-id` exist.
However, `/etc/machine-id`, doesn't change if hardware is replaced, also it is only available on systemd distributions.

I expect a unique system identifier to change, if the CPU is replaced, or the OS is reinstalled.
However, adding/removing/modifying software, network interfaces, user-accounts, other hardware, as well as 
rebooting the system shouldn't result in the unique identifier changing.
Also changing the MAC-address, or modifying the locales shouldn't change the unique identifier.

## How?

To generate the unique identifier, the following attributes are combined and then hashed:

- CPU model name
- Root partition size
- Root partition creation time
- The inode number of /etc
- The inode number of /bin

## Further reading

For more information, feel free to read [my blog post](http://voidptr.xyz/posts/creating_unique_identifiers.html), where I talk I describe this approach in more detail.

