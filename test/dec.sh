#!/bin/bash
decrypt () {
  local key="$1"
  openssl enc -aes-128-ecb -d -nopad \
    -K $(printf "$key" | xxd -p)
}
decrypt "$@"
