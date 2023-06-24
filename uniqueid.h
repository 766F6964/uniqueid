#ifndef UNIQUE_ID_H
#define UNIQUE_ID_H

#include <stdint.h>

/**
 * @brief Obtains the inode for a given file. (Follows symlinks)
 * @param path The path of the file to retrieve the inode value for.
 * @return The inode of the file, or 0x0 in case of failure.
 */
uint64_t get_inode(char *path);

/**
 * @brief Obtains the total size of the root parition in bytes
 * @return The size of 0x0 in case of failure.
*/
uint64_t get_root_part_size(void);

/**
 * @brief Obtains the unix timestamp of the creation time of the root partition.
 * This utilizes the statx struct (introduced in Linux 4.11).
 * @return The unix timestamp of the root partition creation time or 0x0 in case of failure
*/
uint64_t get_root_partition_birth_time(void);

/**
 * @brief Obtains the CPU model name by reading the /proc/cpuinfo file
 * @return The cpu model name or "Unknown" in case of failure
 */
char *get_cpu_model_name(void);

/**
 * @brief Obtains a unique system identifier that remains unchanged when the system is rebooted.
 * @return The unique identifier
*/
char* get_unique_id(void);

#endif