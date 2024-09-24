.data
.global _key_bin
.org 0x20001000
_key_bin:
  .space 128 - (.-_key_bin)
  .incbin "key/key.bin"
