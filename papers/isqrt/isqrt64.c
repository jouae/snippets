#include <stdint.h>

// count leading zeros of nonzero 64-bit unsigned integer
int clz64(uint64_t x);

// isqrt64_tab[k] = isqrt(256*(k+65)-1) for 0 <= k < 192
static const uint8_t isqrt64_tab[192] = {
    128, 129, 130, 131, 132, 133, 134, 135, 136, 137,
    138, 139, 140, 141, 142, 143, 143, 144, 145, 146,
    147, 148, 149, 150, 150, 151, 152, 153, 154, 155,
    155, 156, 157, 158, 159, 159, 160, 161, 162, 163,
    163, 164, 165, 166, 167, 167, 168, 169, 170, 170,
    171, 172, 173, 173, 174, 175, 175, 176, 177, 178,
    178, 179, 180, 181, 181, 182, 183, 183, 184, 185,
    185, 186, 187, 187, 188, 189, 189, 190, 191, 191,
    192, 193, 193, 194, 195, 195, 196, 197, 197, 198,
    199, 199, 200, 201, 201, 202, 203, 203, 204, 204,
    205, 206, 206, 207, 207, 208, 209, 209, 210, 211,
    211, 212, 212, 213, 214, 214, 215, 215, 216, 217,
    217, 218, 218, 219, 219, 220, 221, 221, 222, 222,
    223, 223, 224, 225, 225, 226, 226, 227, 227, 228,
    229, 229, 230, 230, 231, 231, 232, 232, 233, 234,
    234, 235, 235, 236, 236, 237, 237, 238, 238, 239,
    239, 240, 241, 241, 242, 242, 243, 243, 244, 244,
    245, 245, 246, 246, 247, 247, 248, 248, 249, 249,
    250, 250, 251, 251, 252, 252, 253, 253, 254, 254,
    255, 255,
};

// integer square root of a 64-bit unsigned integer
uint32_t isqrt64(uint64_t x)
{
    if (x == 0) return 0;

    int lz = clz64(x) & 62;
    x <<= lz;
    uint32_t y = isqrt64_tab[(x >> 56) - 64];
    y = (y << 7) + (x >> 41) / y;
    y = (y << 15) + (x >> 17) / y;
    y -= x < (uint64_t)y * y;
    return y >> (lz >> 1);
}
