#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <sys/stat.h>

enum {
  KB = 1 << 10,
  MB = KB * KB,
  GB = MB * KB
};

void size_to_str(unsigned int size) {
  if (size >= 0 && size < KB) {
    printf("%d BT\n", size);
  }
  else
  if (size >= KB && size < MB) {
    printf("%4.2lf KB\n", (double)size / KB);
  }
  else
  if (size >= MB && size < GB) {
    printf("%4.2lf MB\n", (double)size / MB);
  }
  else
  if (size >= GB) {
    printf("%4.2lf GB\n", (double)size / GB);
  }
}

void print_data_file(struct stat * stf) {
  if (!stf) {
    exit(3);
  }

  struct tm lt;

  time_t atime    = stf->st_atime;
  time_t mtime    = stf->st_mtime;
  time_t attrtime = stf->st_ctime;

  char abuffer[80];
  char mbuffer[80];
  char attrbuffer[80];

  memset(&lt, 0x00, sizeof(lt));
  localtime_r(&atime, &lt);
  strftime(abuffer, sizeof(abuffer), "%c", &lt);

  memset(&lt, 0x00, sizeof(lt));
  localtime_r(&mtime, &lt);
  strftime(mbuffer, sizeof(mbuffer), "%c", &lt);

  memset(&lt, 0x00, sizeof(lt));
  localtime_r(&attrtime, &lt);
  strftime(attrbuffer, sizeof(attrbuffer), "%c", &lt);

  printf("MODE:\t\t\t%o\n", (unsigned int)(stf->st_mode & 0x00000FFF));

  printf("SIZE:\t\t\t");
    size_to_str(stf->st_size);

  printf("ACCESS_FILE:\t\t%s\n", abuffer);
  printf("MODIFY_FILE:\t\t%s\n", mbuffer);
  printf("CHANGE_ATTR_FILE:\t%s\n", attrbuffer);

  printf("U_ID:\t\t\t%u\n", stf->st_uid);
  printf("GR_ID:\t\t\t%u\n", stf->st_gid);
  printf("ID:\t\t\t%lld\n", stf->st_dev);
  printf("I-NODE:\t\t\tDEC:%10ld | HEX:%10.2lX\n", stf->st_ino, stf->st_ino);
  printf("LINKS:\t\t\t%u\n", stf->st_nlink);
  printf("ID_DEV:\t\t\t%lld\n", stf->st_rdev);

  printf("BLOCK_SIZE:\t\t");
    size_to_str( stf->st_blksize);

  printf("BLOCK_FILE:\t\t%ld\n", stf->st_blocks);

  return;
}

int main(int argc, char * argv[]) {
  struct stat stf;

  int result = 0;
  int fd     = 0;

  if (argc != 2) {
    fprintf(stderr, "[!] Error: Only 1 argument!\n");
    exit(4);
  }

  memset(&stf, 0x00, sizeof(stf));

  fd = open(argv[1], O_RDONLY);

  if (fd == -1) {
    fprintf(stderr, "[!] Error: file not openned!\n");
    exit(1);
  }

  result = fstat(fd, &stf);

  if (result == -1) {
    fprintf(stderr, "[!] Error: no data for file %s!\n", argv[1]);
    close(fd);
    exit(2);
  }

  close(stf);

  printf("FILENAME:\t\t%s\n", argv[1]);
  print_data_file(&stf);

  return 0;
}
