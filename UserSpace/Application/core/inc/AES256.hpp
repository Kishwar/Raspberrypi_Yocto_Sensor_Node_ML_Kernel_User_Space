/******************************************************************************
 *  @file       AES256.hpp
 *  @brief      Obfuscated AES-256 key file
 *
 *  @copyright  Copyright (c) 2025 Kishwar Kumar
 *              All rights reserved.
 *
 *  @license    This project is publicly available on GitHub for viewing and
 *              educational/reference purposes only. Redistribution, modification,
 *              or commercial use of any portion of this code is strictly
 *              prohibited without prior written permission from the author.
 *
 *  @author     Kishwar Kumar
 *  @version    1.0
 *
 *  @note       This code is not open source. Unauthorized use is not permitted.
 ******************************************************************************/

#ifndef _AES256_HPP_
#define _AES256_HPP_

#define AES_KEY_BYTE_COUNT 32

#define IS_INDEX(i, x) (1 / ((((i)-(x)) * ((i)-(x))) + 1))

#define AES_OBF_0(i) (((( 8 * ((i) + 2) ) + 62) ^ 199) & 0xFF) * IS_INDEX(i, 0)
#define AES_OBF_1(i) (((( 6 * ((i) + 2) ) + 124) ^ 251) & 0xFF) * IS_INDEX(i, 1)
#define AES_OBF_2(i) (((( 15 * ((i) + 5) ) + 209) ^ 232) & 0xFF) * IS_INDEX(i, 2)
#define AES_OBF_3(i) (((( 13 * ((i) + 7) ) + 146) ^ 2) & 0xFF) * IS_INDEX(i, 3)
#define AES_OBF_4(i) (((( 5 * ((i) + 3) ) + 27) ^ 164) & 0xFF) * IS_INDEX(i, 4)
#define AES_OBF_5(i) (((( 9 * ((i) + 7) ) + 186) ^ 117) & 0xFF) * IS_INDEX(i, 5)
#define AES_OBF_6(i) (((( 10 * ((i) + 7) ) + 60) ^ 122) & 0xFF) * IS_INDEX(i, 6)
#define AES_OBF_7(i) (((( 13 * ((i) + 7) ) + 205) ^ 157) & 0xFF) * IS_INDEX(i, 7)
#define AES_OBF_8(i) (((( 8 * ((i) + 5) ) + 208) ^ 74) & 0xFF) * IS_INDEX(i, 8)
#define AES_OBF_9(i) (((( 7 * ((i) + 7) ) + 127) ^ 39) & 0xFF) * IS_INDEX(i, 9)
#define AES_OBF_10(i) (((( 2 * ((i) + 2) ) + 1) ^ 22) & 0xFF) * IS_INDEX(i, 10)
#define AES_OBF_11(i) (((( 12 * ((i) + 2) ) + 18) ^ 56) & 0xFF) * IS_INDEX(i, 11)
#define AES_OBF_12(i) (((( 13 * ((i) + 5) ) + 34) ^ 246) & 0xFF) * IS_INDEX(i, 12)
#define AES_OBF_13(i) (((( 14 * ((i) + 2) ) + 146) ^ 190) & 0xFF) * IS_INDEX(i, 13)
#define AES_OBF_14(i) (((( 13 * ((i) + 4) ) + 31) ^ 17) & 0xFF) * IS_INDEX(i, 14)
#define AES_OBF_15(i) (((( 8 * ((i) + 3) ) + 160) ^ 180) & 0xFF) * IS_INDEX(i, 15)
#define AES_OBF_16(i) (((( 3 * ((i) + 1) ) + 21) ^ 111) & 0xFF) * IS_INDEX(i, 16)
#define AES_OBF_17(i) (((( 15 * ((i) + 4) ) + 242) ^ 238) & 0xFF) * IS_INDEX(i, 17)
#define AES_OBF_18(i) (((( 10 * ((i) + 6) ) + 135) ^ 24) & 0xFF) * IS_INDEX(i, 18)
#define AES_OBF_19(i) (((( 10 * ((i) + 4) ) + 223) ^ 186) & 0xFF) * IS_INDEX(i, 19)
#define AES_OBF_20(i) (((( 9 * ((i) + 3) ) + 69) ^ 41) & 0xFF) * IS_INDEX(i, 20)
#define AES_OBF_21(i) (((( 9 * ((i) + 2) ) + 38) ^ 12) & 0xFF) * IS_INDEX(i, 21)
#define AES_OBF_22(i) (((( 13 * ((i) + 1) ) + 201) ^ 127) & 0xFF) * IS_INDEX(i, 22)
#define AES_OBF_23(i) (((( 6 * ((i) + 1) ) + 98) ^ 74) & 0xFF) * IS_INDEX(i, 23)
#define AES_OBF_24(i) (((( 14 * ((i) + 6) ) + 79) ^ 116) & 0xFF) * IS_INDEX(i, 24)
#define AES_OBF_25(i) (((( 5 * ((i) + 6) ) + 67) ^ 9) & 0xFF) * IS_INDEX(i, 25)
#define AES_OBF_26(i) (((( 9 * ((i) + 2) ) + 42) ^ 205) & 0xFF) * IS_INDEX(i, 26)
#define AES_OBF_27(i) (((( 4 * ((i) + 6) ) + 89) ^ 57) & 0xFF) * IS_INDEX(i, 27)
#define AES_OBF_28(i) (((( 3 * ((i) + 7) ) + 84) ^ 19) & 0xFF) * IS_INDEX(i, 28)
#define AES_OBF_29(i) (((( 6 * ((i) + 4) ) + 251) ^ 4) & 0xFF) * IS_INDEX(i, 29)
#define AES_OBF_30(i) (((( 3 * ((i) + 6) ) + 251) ^ 1) & 0xFF) * IS_INDEX(i, 30)
#define AES_OBF_31(i) (((( 4 * ((i) + 3) ) + 46) ^ 245) & 0xFF) * IS_INDEX(i, 31)

#define AES_KEY_BYTE(i) ( \
    AES_OBF_0(i) + \
    AES_OBF_1(i) + \
    AES_OBF_2(i) + \
    AES_OBF_3(i) + \
    AES_OBF_4(i) + \
    AES_OBF_5(i) + \
    AES_OBF_6(i) + \
    AES_OBF_7(i) + \
    AES_OBF_8(i) + \
    AES_OBF_9(i) + \
    AES_OBF_10(i) + \
    AES_OBF_11(i) + \
    AES_OBF_12(i) + \
    AES_OBF_13(i) + \
    AES_OBF_14(i) + \
    AES_OBF_15(i) + \
    AES_OBF_16(i) + \
    AES_OBF_17(i) + \
    AES_OBF_18(i) + \
    AES_OBF_19(i) + \
    AES_OBF_20(i) + \
    AES_OBF_21(i) + \
    AES_OBF_22(i) + \
    AES_OBF_23(i) + \
    AES_OBF_24(i) + \
    AES_OBF_25(i) + \
    AES_OBF_26(i) + \
    AES_OBF_27(i) + \
    AES_OBF_28(i) + \
    AES_OBF_29(i) + \
    AES_OBF_30(i) + \
    AES_OBF_31(i) )

#endif  // _AES256_HPP_
