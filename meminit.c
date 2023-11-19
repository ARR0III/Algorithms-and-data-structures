size_t * meminit(void * ptr, size_t data, size_t size) {
#ifdef __ASM_32_X86_CPP_BUILDER__
_asm {
  mov ecx, size
  mov edx, data
  mov edi, ptr

  cmp edx, 0xFF
  ja _meminit

  mov dh, dl
  mov ebx, edx
  shl ebx, 16
  or  edx, ebx

_meminit:
  mov ebx, ecx
  and ebx, 3

  shr ecx, 2  /* sum blocks for writing */
  jz _meminit_byte

_meminit_dword:
  mov dword[edi], edx
  add edi, 4
  dec ecx
  jz _meminit_byte
  mov dword[edi], edx
  add edi, 4
  dec ecx
  jz _meminit_byte
  mov dword[edi], edx
  add edi, 4
  dec ecx
  jz _meminit_byte
  mov dword[edi], edx
  add edi, 4
  dec ecx
  jz _meminit_byte
  jmp _meminit_dword

_meminit_byte:
  test ebx, ebx
  jz _exit
  mov byte[edi], dl
  inc edi
  dec ebx
  jmp _meminit_byte

_exit:
}
#else
  unsigned char * p = (unsigned char *)ptr;
  size_t c, o, dword = data;

  if (data < 256) {
    dword |= data  <<  8;
    dword |= dword << 16;
  }

  c = size >> 2; /* blocks of 4 bytes */
  o = size  & 3; /* bytes not in 1 block */

  while (c) {
    *((size_t *)p) = dword;

    p += sizeof(size_t);
    c--;
  }

  while (o) {
    (*p) = (unsigned char)dword;

    p++;
    o--;
  }
#endif
  return ptr;
}

