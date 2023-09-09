/*
 * Copyright (c) 2022, Samsung Electronics Co. Ltd All Rights Reserved
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include <fstab/fstab.h>
#include <android-base/properties.h>
#include <android-base/logging.h>

#include <exynos_message/exynos_message.h>

namespace android {
namespace hardware {
namespace samsung_slsi {
namespace exynos_bootloader_message {

using android::fs_mgr::Fstab;
using android::fs_mgr::ReadDefaultFstab;

bool Exynos_Bootloader_Message::open_message(const char *msg_device) {
  Fstab fstab;
  if (!ReadDefaultFstab(&fstab)) {
    LOG(ERROR) << "ERROR: Cannot Open fstab";
	return false;
  }

  for (const auto& entry : fstab) {
    if (entry.mount_point == msg_device) {
      if (entry.blk_device.empty()) {
        LOG(ERROR) << "ERROR: The path of message device is empty";
		return false;
	  }
	  exynos_message_fd = open(entry.blk_device.c_str(), O_RDWR);
	  if (exynos_message_fd == -1) {
        LOG(ERROR) << "ERROR: cannot open " << msg_device << " with fd";
		return false;
	  } else {
        return true;
	  }
	}
  }
  LOG(ERROR) << "ERROR: Cannot find " << msg_device << "from fstab";
  return false;
}

void Exynos_Bootloader_Message::close_message() {
  close(exynos_message_fd);
  exynos_message_fd = -1;
}

bool Exynos_Bootloader_Message::read_message(void *buf, size_t offset, size_t msg_size) {
   if (exynos_message_fd == -1) {
    LOG(ERROR) << "ERROR: cannot load: Not Opened";
	return false;
  }

 // Load behavior
  int seeked_byte = lseek(exynos_message_fd, offset, SEEK_SET);
  if (seeked_byte != offset) {
    LOG(ERROR) << "ERROR: Cannot seek message device: " << seeked_byte;
	return false;
  }

  ssize_t num_read;
  do {
    num_read = read(exynos_message_fd, buf, msg_size);
  } while (num_read == -1 && errno == EINTR);

  if (num_read != msg_size) {
    PLOG(ERROR) << "ERROR: read bytes length is not matched with message size: "
	            << num_read << " != " << msg_size;
    return false;
  }
  return true;
}

bool Exynos_Bootloader_Message::write_message(void *buf, size_t offset, size_t msg_size) {
  if (exynos_message_fd == -1) {
    LOG(ERROR) << "ERROR: cannot save: Not opened";
	return false;
  }

  // Save behavior
  int seeked_byte = lseek(exynos_message_fd, offset, SEEK_SET);
  if (seeked_byte != offset) {
    LOG(ERROR) << "ERROR: Cannot seek message device: " << seeked_byte;
	return false;
  }

  ssize_t num_written;
  do {
    num_written = write(exynos_message_fd, buf, msg_size);
  } while (num_written == -1 && errno == EINTR);

  if (num_written != msg_size) {
    PLOG(ERROR) << "ERROR: written bytes length is not matched with message size: "
	            << num_written << " != " << msg_size;
    return false;
  }
  return true;
}

} // namespace exynos_bootloader_message
} // namespace samsung_slsi
} // namespace hardware
} // namespace android
