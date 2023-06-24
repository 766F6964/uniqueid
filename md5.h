#ifndef MD5_H
#define MD5_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    uint64_t size;        // Size of input in bytes
    uint32_t buffer[4];   // Current accumulation of hash
    uint8_t input[64];    // Input to be used in the next step
    uint8_t digest[16];   // Result of algorithm
} MD5Context;

/**
 * @brief Initializes a new MD5 context
 * @param ctx The context
 */
void md5_init(MD5Context *ctx);

/**
 * @brief Adds some amount of input to the context. If f the input fills out a block
 * of 512 bits, apply the algorithm (md5_step) and save the result in the buffer.
 * Also updates the overall size.
 * @param ctx The context
 * @param input The input data
 * @param input_len The length of the input data
 */
void md5_update(MD5Context *ctx, uint8_t *input, size_t input_len);

/**
 * @brief Pad the current input to get to 448 bytes, append the size in bits to the very end,
 * and save the result of the final iteration into digest.
 * @param ctx The context
 */
void md5_finalize(MD5Context *ctx);

/**
 * @brief Step on 512 bits of input with the main MD5 algorithm.
 * @param buffer The buffer to process
 * @param input The input data
 */
void md5_step(uint32_t *buffer, uint32_t *input);

/**
 * @brief Computes the MD5 hash of the input.
 * @param data The data to hash
 * @param data_len The length of the data to hash
 * @param result The hash digest as hexadecimal string
 */
void md5_generate(char *data, int data_len, char *result);

#endif