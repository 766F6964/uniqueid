#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/vfs.h>
#include <sys/syscall.h>
#include <linux/stat.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include "uniqueid.h"
#include "md5.h"

uint64_t get_inode(char *path) {
    struct stat file_stat;
    if (stat(path, &file_stat) == -1) {
        return (uint64_t) 0x0;
    }
    return (uint64_t) file_stat.st_ino;
}

uint64_t get_root_part_size(void) {
    struct statfs stat;
    if (statfs("/", &stat) == 0) {
        return (uint64_t)(stat.f_bsize * stat.f_blocks);
    }
    return 0x0;
}

uint64_t get_root_partition_birth_time(void) {
    struct statx statbuf;
    if (syscall(__NR_statx, AT_FDCWD, "/", AT_SYMLINK_NOFOLLOW, STATX_ALL, &statbuf) < 0) {
        return 0x0;
    }
    return (uint64_t)statbuf.stx_btime.tv_sec;
}

char *get_cpu_model_name(void) {
    FILE *cpu_info = fopen("/proc/cpuinfo", "r");
    if (!cpu_info) {
        return strdup("Unknown");
    }
    char name_buffer[256];
    while (fgets(name_buffer, sizeof(name_buffer), cpu_info) != NULL) {
        if (strncmp(name_buffer, "model name", 10) == 0) {
            char *delimiter = strchr(name_buffer + 10, ':');
            if (delimiter != NULL) {
                char *cpu_name = strdup(delimiter + 2);
                size_t length = strcspn(cpu_name, "\n");
                cpu_name[length] = '\0';
                fclose(cpu_info);
                return cpu_name;
            }
        }
    }
    fclose(cpu_info);
    return strdup("Unknown");
}

char* get_unique_id(void) {

    // Obtain all identifiers
    char *cpu_name = get_cpu_model_name();
    uint64_t bin_inode = get_inode("/bin");
    uint64_t etc_inode = get_inode("/etc");
    uint64_t root_size = get_root_part_size();
    uint64_t root_date = get_root_partition_birth_time();

    // Allocate memory to hold all identifiers
    size_t identifier_buf_len = strlen(cpu_name) + 1 + sizeof(uint64_t) * 4;
    char *identifier_buf = calloc(identifier_buf_len, 1);

    // Combine all the identifiers
    memcpy(identifier_buf, cpu_name, strlen(cpu_name));
    char *current_pos = identifier_buf + strlen(cpu_name);
    memcpy(current_pos, &bin_inode, sizeof(uint64_t));
    current_pos += sizeof(uint64_t);
    memcpy(current_pos, &etc_inode, sizeof(uint64_t));
    current_pos += sizeof(uint64_t);
    memcpy(current_pos, &root_size, sizeof(uint64_t));
    current_pos += sizeof(uint64_t);
    memcpy(current_pos, &root_date, sizeof(uint64_t));

    // Compute the md5 hash of the combined values
    char *unique_id = calloc(1, 32);
    md5_generate(identifier_buf, identifier_buf_len, unique_id);
    free(identifier_buf);

    return unique_id;
}