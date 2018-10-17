/* usbreset -- send a USB port reset to a USB device */

/* Taken from:
   https://askubuntu.com/questions/645/how-do-you-reset-a-usb-device-from-the-command-line
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <linux/usbdevice_fs.h>


int main(int argc, char **argv) {
  const char *filename;
  int fd;
  int rc;

  if (argc != 2) {
    fprintf(stderr, "Usage: usbreset <device-filename>\n");
    fprintf(stderr, "Example: usbreset /dev/bus/usb/002/003\n");
    exit(1);
  }

  filename = argv[1];

  fd = open(filename, O_WRONLY);
  if (fd < 0) {
    perror("Error opening output file");
    exit(1);
  }

  printf("Resetting USB device %s\n", filename);
  rc = ioctl(fd, USBDEVFS_RESET, 0);
  if (rc < 0) {
    perror("Error in ioctl");
    exit(1);
  }

  printf("Reset successful\n");

  close(fd);
  exit(0);
}

