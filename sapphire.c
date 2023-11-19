/*
  Plexus Technology Cybernetic Laboratories 2010 - 2022;
  Polyalphabetic substitution cipher "Sapphire";
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define ENCRYPT 1
#define DECRYPT 0

#define BUFFER_SIZE 2048

typedef struct {
  uint8_t key [BUFFER_SIZE];
  uint8_t data[BUFFER_SIZE];
  uint8_t mix [BUFFER_SIZE * 3];
} CRYPT_CTX;

uint32_t gamma = 0;
uint32_t temp  = 0;
uint32_t n     = 0;

void init(uint8_t * key, size_t klen) {
  size_t i;

  for (i = 0; i < klen; ++i) {
    temp += key[i] * (i + 1);
  }
}

int enmix(uint8_t * in, uint8_t * out, size_t ilen) {
  size_t i, j;

  for (i = 0, j = 0; i < ilen; ++i) {
    if (in[i] >= 'A' && in[i] <= 'Z') {
      out[j] = in[i];
      ++j;
      ++n;
    }
    else
    if (in[i] >= 'a' && in[i] <= 'z') {
      out[j] = in[i] - 32;
      ++j;
      ++n;
    }
    else {
      continue;
    }

    if (0 == (n % 6)) {
      out[j] = ' ';
      ++j;
    }

    if (54 == n) {
      out[j] = '\n';
      ++j;
      n = 0;
    }
  }
  out[j] = '\n';
  return j;
}

void crypt(uint8_t * data, uint8_t * key, uint32_t dlen, uint32_t klen, int tumbler) {
  if (NULL == data || NULL == key || 0 == dlen || 0 == klen)
    return;

  uint32_t i;

  for (i = 0; i < dlen; ++i) {
    if (data[i] >= 'a' && data[i] <= 'z') {
      data[i] -= 32;
    }

    if (data[i] >= 'A' && data[i] <= 'Z') {

      temp  += key[gamma % klen];
      temp  += key[temp  % klen];

      temp  += gamma + 1;
      gamma += temp  - 1;

      temp  = (temp % 26) + 'A';

      if (ENCRYPT == tumbler)
        data[i] = ((data[i]  + temp) % 26) + 'A';
      else
        data[i] = (((data[i] - temp) + 26) % 26) + 'A';

    }
  }
}

int main(int argc, char * argv[]) {
  CRYPT_CTX * ctx = NULL;
              ctx = (CRYPT_CTX *)malloc(sizeof(CRYPT_CTX));

  if (NULL == ctx) {
    printf("error: cannot allocate memory!\n");
    return -2;
  }

  if (5 != argc) {
    printf("error: %s [input] [output] [password] [0 or 1]\n", argv[0]);
    free(ctx);
    return 0;
  }

  int tumbler = atoi(argv[argc - 1]);
  int klen    = strlen(argv[argc - 2]);

  if (klen < 0 || klen > BUFFER_SIZE) {
    klen = 2048;
  }

  if (tumbler < 0 || tumbler > 1) {
    printf("error: \"%s\" not number [0..1]\n", argv[argc - 1]);
    free(ctx);
    return -1;
  }

  FILE * fi = fopen(argv[1], "rb");
  FILE * fo = fopen(argv[2], "wb");

  if (NULL == fi) {
    printf("error: file %s not open\n", argv[1]);

    free(ctx);
    fclose(fo);

    return -1;
  }

  if (NULL == fo) {
    printf("error: file %s not open\n", argv[2]);

    free(ctx);
    fclose(fi);

    return -1;
  }

  size_t read;
  int    ret_s;

  memcpy(ctx->key, argv[argc - 2], klen);

  init(ctx->key, klen);

  while (1) {
    read = fread(ctx->data, 1, BUFFER_SIZE, fi);

    if (ENCRYPT == tumbler) {
      ret_s = enmix(ctx->data, ctx->mix, read);
    }

    crypt(tumbler ? ctx->mix : ctx->data, ctx->key,
          tumbler ? ret_s    : read, klen, tumbler);

    if (fwrite(tumbler ? ctx->mix : ctx->data, 1,
               tumbler ?  ret_s   : read, fo) != (tumbler ? ret_s : read)) {

      printf("error writing in output stream!\n");
      break;
    }

    fflush(fo);

    if (read < BUFFER_SIZE)
      break;
  }

  fclose(fi);
  fclose(fo);

  memset(ctx, 0x00, sizeof(CRYPT_CTX));

  free(ctx);
  return 0;
}
