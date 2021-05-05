#include "os.h"

#define R(r) ((volatile uint32 *)(0x10001000 + (r)))

static struct disk
{
  char pages[2 * PGSIZE];
  /* descriptor */
  virtq_desc_t *desc;
  /* AvailableRing */
  virtq_avail_t *avail;
  /* UsedRing */
  virtq_used_t *used;
  /* For decord each descriptor is free or not */
  char free[NUM];
  /* Disk command headers */
  virtio_blk_req_t ops[NUM];
} __attribute__((aligned(PGSIZE))) disk;

void disk_init()
{
  uint32 status = 0;
  if (*R(VIRTIO_MMIO_MAGIC_VALUE) != 0x74726976 ||
      *R(VIRTIO_MMIO_VERSION) != 1 ||
      *R(VIRTIO_MMIO_DEVICE_ID) != 2 ||
      *R(VIRTIO_MMIO_VENDOR_ID) != 0x554d4551)
  {
    lib_puts("could not find virtio disk\n");
  }
  /* Set the ACKNOWLEDGE status bit to the status register. */
  status |= VIRTIO_CONFIG_S_ACKNOWLEDGE;
  *R(VIRTIO_MMIO_STATUS) = status;
  /* Set the DRIVER status bit to the status register. */
  status |= VIRTIO_CONFIG_S_DRIVER;
  *R(VIRTIO_MMIO_STATUS) = status;
  /* negotiate features */
  uint64 features = *R(VIRTIO_MMIO_DEVICE_FEATURES);
  features &= ~(1 << VIRTIO_BLK_F_RO);
  features &= ~(1 << VIRTIO_BLK_F_SCSI);
  features &= ~(1 << VIRTIO_BLK_F_CONFIG_WCE);
  features &= ~(1 << VIRTIO_BLK_F_MQ);
  features &= ~(1 << VIRTIO_F_ANY_LAYOUT);
  features &= ~(1 << VIRTIO_RING_F_EVENT_IDX);
  features &= ~(1 << VIRTIO_RING_F_INDIRECT_DESC);
  *R(VIRTIO_MMIO_DRIVER_FEATURES) = features;

  /* tell device that feature negotiation is complete. */
  status |= VIRTIO_CONFIG_S_FEATURES_OK;
  *R(VIRTIO_MMIO_STATUS) = status;

  /* tell device we're completely ready. */
  status |= VIRTIO_CONFIG_S_DRIVER_OK;
  *R(VIRTIO_MMIO_STATUS) = status;

  *R(VIRTIO_MMIO_GUEST_PAGE_SIZE) = PGSIZE;
  /* initialize queue 0. */
  *R(VIRTIO_MMIO_QUEUE_SEL) = 0;
  uint32 max = *R(VIRTIO_MMIO_QUEUE_NUM_MAX);
  if (max == 0)
    lib_puts("virtio disk has no queue 0\n");
  if (max < NUM)
    lib_puts("virtio disk max queue too short\n");
  *R(VIRTIO_MMIO_QUEUE_NUM) = NUM;
  memset(disk.pages, 0, sizeof(disk.pages));
  *R(VIRTIO_MMIO_QUEUE_PFN) = ((uint64)disk.pages) >> PGSHIFT;

  // desc = pages -- num * virtq_desc
  // avail = pages + 0x40 -- 2 * uint16, then num * uint16
  // used = pages + 4096 -- 2 * uint16, then num * vRingUsedElem

  disk.desc = (struct virtq_desc *)disk.pages;
  disk.avail = (struct virtq_avail *)(disk.pages + NUM * sizeof(struct virtq_desc));
  disk.used = (struct virtq_used *)(disk.pages + PGSIZE);

  // all NUM descriptors start out unused.
  for (int i = 0; i < NUM; i++)
    disk.free[i] = 1;
  lib_puts("Disk init work is success!\n");
}