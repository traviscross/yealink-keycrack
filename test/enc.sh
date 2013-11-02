#!/bin/bash
encrypt () {
 local key="$1"
  openssl enc -aes-128-ecb -nopad \
    -K $(printf "$key" | xxd -p)
}
encrypt "$@"
