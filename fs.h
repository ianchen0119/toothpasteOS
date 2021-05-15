#ifndef __FS_H__
#define __FS_H__

#include "types.h"

#define BLOCKSIZE 128
#define IPB (BLOCKSIZE / sizeof(struct inode))

/* Layout of the first fs block group
 * +--+--+--+--+--+
 * |sb|fd|bm|im|db|
 * +--+--+--+--+--+
 * sb: superblock
 * fd: file descriptor
 * bm: block bitmap
 * im: inode bitmap
 * db: data block
 */

struct superblock
{

  uint32 inodes_count;
  uint32 blocks_count;
  uint32 free_inodes_count;
  uint32 free_blocks_count;
  uint16 magic;
};

struct inode
{
  uint16 type;
  uint32 file_size;
};

#define DIRSIZ 14

struct dirent
{
  ushort inum;
  char name[DIRSIZ];
};

#endif
