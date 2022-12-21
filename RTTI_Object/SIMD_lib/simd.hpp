/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <type_traits>
#include <utility>
#include <cstdint>

#ifndef INLINE
#define INLINE inline __attribute__((always_inline))
#endif

#ifndef ASSUME_ALIGNED
#define ASSUME_ALIGNED(address, alignment) __builtin_assume_aligned(address, alignment)
#endif

#ifndef ATTRIBUTE
#define ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#endif

#ifndef BUILTIN
#define BUILTIN(name) __builtin_ia32_##name
#endif

#ifndef MIN_VECTOR_WIDTH
#define MIN_VECTOR_WIDTH(width) __attribute__((min_vector_width(width)))
#endif

#ifndef VECTOR_REGISTER_ITERATOR
#define VECTOR_REGISTER_ITERATOR(Vector) __builtin_bit_cast(Simd::ElementType<decltype(Vector)>[Simd::NumElements<decltype(Vector)>()], Vector)
#endif

#ifdef __AVX__
#define AVX __AVX__
#pragma message "AVX supported"
#endif
#ifdef __AVX2__
#define AVX2 __AVX2__
#pragma message "AVX2 supported"
#endif

#ifdef __AVX512__
#define AVX512 __AVX512__
#pragma message "AVX512 supported"
#endif

template<typename T>
using Vector4 = T __attribute__((vector_size(4), aligned(4)));

using char8_4 = Vector4<char8_t>; static_assert(alignof(char8_4) == 4);
using uint8_4 = Vector4<uint8_t>; static_assert(alignof(uint8_4) == 4);
using int8_4 = Vector4<int8_t>; static_assert(alignof(int8_4) == 4);
using uint16_2 = Vector4<uint16_t>; static_assert(alignof(uint16_2) == 4);
using int16_2 = Vector4<int16_t>; static_assert(alignof(int16_2) == 4);

template<typename T>
using Vector8 = T __attribute__((vector_size(8), aligned(8)));

using char8x8 = Vector8<char8_t>; static_assert(alignof(char8x8) == 8);
using uint8x8 = Vector8<uint8_t>; static_assert(alignof(uint8x8) == 8);
using int8x8 = Vector8<int8_t>; static_assert(alignof(int8x8) == 8);
using uint16x4 = Vector8<uint16_t>; static_assert(alignof(uint16x4) == 8);
using int16x4 = Vector8<int16_t>; static_assert(alignof(int16x4) == 8);
using uint32x2 = Vector8<uint32_t>; static_assert(alignof(uint32x2) == 8);
using int32x2 = Vector8<int32_t>; static_assert(alignof(int32x2) == 8);
using float32x2 = Vector8<float>; static_assert(alignof(float32x2) == 8);

template<typename T>
using Vector16 = T __attribute__((vector_size(16), aligned(16)));

using char8x16 = Vector16<char8_t>; static_assert(alignof(char8x16) == 16);
using char16x8 = Vector16<char16_t>; static_assert(alignof(char16x8) == 16);
using char32x4 = Vector16<char32_t>; static_assert(alignof(char32x4) == 16);
using uint8x16 = Vector16<uint8_t>; static_assert(alignof(uint8x16) == 16);
using int8x16 = Vector16<int8_t>; static_assert(alignof(int8x16) == 16);
using uint16x8 = Vector16<uint16_t>; static_assert(alignof(uint16x8) == 16);
using int16x8 = Vector16<int16_t>; static_assert(alignof(int16x8) == 16);
using uint32x4 = Vector16<uint32_t>; static_assert(alignof(uint32x4) == 16);
using int32x4 = Vector16<int32_t>; static_assert(alignof(int32x4) == 16);
using uint64x2 = Vector16<uint64_t>; static_assert(alignof(uint64x2) == 16);
using int64x2 = Vector16<int64_t>; static_assert(alignof(int64x2) == 16);
using float32x4 = Vector16<float>; static_assert(alignof(float32x4) == 16);
using float64x2 = Vector16<double>; static_assert(alignof(float64x2) == 16);

template<typename T>
using Vector32 = T __attribute__((vector_size(32), aligned(32)));

using char8x32 = Vector32<char8_t>; static_assert(alignof(char8x32) == 32);
using char16x16 = Vector32<char16_t>; static_assert(alignof(char16x16) == 32);
using char32x8 = Vector32<char32_t>; static_assert(alignof(char32x8) == 32);
using uint8x32 = Vector32<uint8_t>; static_assert(alignof(uint8x32) == 32);
using int8x32 = Vector32<int8_t>; static_assert(alignof(int8x32) == 32);
using uint16x16 = Vector32<uint16_t>; static_assert(alignof(uint16x16) == 32);
using int16x16 = Vector32<int16_t>; static_assert(alignof(int16x16) == 32);
using uint32x8 = Vector32<uint32_t>; static_assert(alignof(uint32x8) == 32);
using int32x8 = Vector32<int32_t>; static_assert(alignof(int32x8) == 32);
using uint64x4 = Vector32<uint64_t>; static_assert(alignof(uint64x4) == 32);
using int64x4 = Vector32<int64_t>; static_assert(alignof(int64x4) == 32);
using float32x8 = Vector32<float>; static_assert(alignof(float32x8) == 32);
using float64x4 = Vector32<double>; static_assert(alignof(float64x4) == 32);

template<typename T>
using Vector64 = T __attribute__((vector_size(64), aligned(64)));

using char8x64 = Vector64<char8_t>; static_assert(alignof(char8x64) == 64);
using char16x32 = Vector64<char16_t>; static_assert(alignof(char16x32) == 64);
using char32x16 = Vector64<char32_t>; static_assert(alignof(char32x16) == 64);
using uint8x64 = Vector64<uint8_t>; static_assert(alignof(uint8x64) == 64);
using int8x64 = Vector64<int8_t>; static_assert(alignof(int8x64) == 64);
using uint16x32 = Vector64<uint16_t>; static_assert(alignof(uint16x32) == 64);
using int16x32 = Vector64<int16_t>; static_assert(alignof(int16x32) == 64);
using uint32x16 = Vector64<uint32_t>; static_assert(alignof(uint32x16) == 64);
using int32x16 = Vector64<int32_t>; static_assert(alignof(int32x16) == 64);
using uint64x8 = Vector64<uint64_t>; static_assert(alignof(uint64x8) == 64);
using int64x8 = Vector64<int64_t>; static_assert(alignof(int64x8) == 64);
using float32x16 = Vector64<float>; static_assert(alignof(float32x16) == 64);
using float64x8 = Vector64<double>; static_assert(alignof(float64x8) == 64);

namespace Simd
{

    template<typename RegisterType>
    using ElementType = std::remove_cvref_t<decltype(RegisterType{}[0])>;

    template<typename RegisterType>
    inline consteval uint64_t ElementSize()
    {
        return sizeof(ElementType<RegisterType>);
    }

    template<typename RegisterType>
    inline consteval uint64_t NumElements()
    {
        return alignof(RegisterType) / ElementSize<RegisterType>();
    }

    INLINE void ZeroUpper()
    {
#ifdef AVX2
        BUILTIN(vzeroupper)();
#endif
    }

    INLINE void ZeroAll()
    {
#ifdef AVX2
        BUILTIN(vzeroall)();
#endif
    }

    template<typename RegisterType>
    INLINE constexpr RegisterType SetAll(ElementType<RegisterType> Value)
    {
        auto FillValues = [Value]<std::size_t... I>(std::index_sequence<I...>) -> RegisterType
        {
            return RegisterType{((void)I, Value)...};
        };

        return FillValues(std::make_index_sequence<NumElements<RegisterType>()>{});
    }

    template<int32_t... Index, typename VectorType>
    INLINE constexpr VectorType ShuffleVector(VectorType Low, VectorType High)
    {
        return __builtin_shufflevector(Low, High, Index...);
    }

#ifdef AVX

    ATTRIBUTE(warn_unused_result, always_inline)
    inline uint8x16 CopyOrZero(const uint8x16 Source, const uint8x16 Mask)
    {
        return BUILTIN(pshufb128)(Source, Mask);
    }

#endif
#ifdef AVX2

    ATTRIBUTE(warn_unused_result, always_inline)
    inline uint8x32 CopyOrZero(const uint8x32 Source, const uint8x32 Mask)
    {
        return BUILTIN(pshufb256)(Source, Mask);
    }

#endif
#ifdef AVX

    template<typename RegisterType> requires(alignof(RegisterType) == 16)
    inline constexpr int32_t Mask()
    {
        if constexpr(NumElements<RegisterType>() == 16)
        {
            return static_cast<int32_t>(0b00000000000000001111111111111111);
        }
        else if constexpr(NumElements<RegisterType>() == 8)
        {
            return static_cast<int32_t>(0b00000000000000000000000011111111);
        }
        else if constexpr(NumElements<RegisterType>() == 4)
        {
            return static_cast<int32_t>(0b00000000000000000000000000001111);
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename RegisterType> requires(alignof(RegisterType) == 32)
    inline constexpr int32_t Mask()
    {
        if constexpr(NumElements<RegisterType>() == 32)
        {
            return static_cast<int32_t>(0b11111111111111111111111111111111);
        }
        else if constexpr(NumElements<RegisterType>() == 16)
        {
            return static_cast<int32_t>(0b11111111111111111111111111111111);
        }
        else if constexpr(NumElements<RegisterType>() == 8)
        {
            return static_cast<int32_t>(0b00000000000000000000000011111111);
        }
        else if constexpr(NumElements<RegisterType>() == 4)
        {
            return static_cast<int32_t>(0b00000000000000000000000000001111);
        }
    }

#endif //AVX2
#ifdef AVX512

    template<typename RegisterType> requires(alignof(RegisterType) == 64)
    inline constexpr auto Mask()
    {
        if constexpr(NumElements<RegisterType>() == 64)
        {
            return static_cast<uint64_t>(~0ULL);
        }
        else if constexpr(NumElements<RegisterType>() == 32)
        {
            return static_cast<uint32_t>(~0U);
        }
        else if constexpr(NumElements<RegisterType>() == 16)
        {
            return static_cast<uint16_t>(~0U);
        }
        else if constexpr(NumElements<RegisterType>() == 8)
        {
            return static_cast<uint8_t>(~0U);
        }
    }

#endif //AVX512

    template<typename T>
    using MaskType = decltype(Mask<T>());

#ifdef AVX

    template<typename T>
    INLINE constexpr int32_t MoveMask(Vector16<T> VectorMask) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(sizeof(T) <= 2)
        {
            return BUILTIN(pmovmskb128)(VectorMask); //no movemask function exist for words actual mask looks like 0b01010101010101010101010101010101
        }
        else if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(movmskps)(VectorMask);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(movmskpd)(VectorMask);
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T>
    INLINE constexpr int32_t MoveMask(Vector32<T> VectorMask) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(sizeof(T) <= 2)
        {
            return BUILTIN(pmovmskb256)(VectorMask); //no movemask function exist for words
        }
        else if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(movmskps256)(VectorMask);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(movmskpd256)(VectorMask);
        }
    }

#endif //AVX2
#ifdef AVX512

    template<typename T>
    INLINE constexpr decltype(Mask<Vector64<T>>()) MoveMask(Vector64<T> VectorMask) MIN_VECTOR_WIDTH(512)
    {
        if constexpr(sizeof(T) == 1)
        {
            return BUILTIN(cvtb2mask512)(VectorMask);
        }
        else if constexpr(sizeof(T) == 2)
        {
            return BUILTIN(cvtw2mask512)(VectorMask);
        }
        else if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(cvtd2mask512)(VectorMask);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(cvtq2mask512)(VectorMask);
        }
    }

#endif //AVX512
#ifdef AVX

    template<typename T> requires(sizeof(T) >= 4)
    INLINE constexpr Vector16<T> MaskLoad(const void* const Value, Vector16<T> Mask) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(maskloadps)(Value, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(maskloadpd)(Value, Mask);
            }
        }
        else if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(maskloadd)(Value, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(maskloadq)(Value, Mask);
            }
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T> requires(sizeof(T) >= 4)
    INLINE constexpr Vector32<T> MaskLoad(const void* const Value, Vector32<T> Mask) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(maskloadps256)(Value, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(maskloadpd256)(Value, Mask);
            }
        }
        else if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(maskloadd256)(Value, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(maskloadq256)(Value, Mask);
            }
        }
    }

#endif //AVX2
#ifdef AVX512

    template<typename T> requires(sizeof(T) >= 4)
    INLINE constexpr Vector64<T> MaskLoadAligned(void* const Address, decltype(Mask<Vector64<T>>()) Mask, Vector64<T> ReplacementValues = Simd::SetAll<Vector64<T>>(0)) MIN_VECTOR_WIDTH(512)
    {
        if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(loadaps512_mask)(Address, ReplacementValues, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(loadapd512_mask)(Address, ReplacementValues, Mask);
            }
        }
        else if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(movdqa32load512_mask)(Address, ReplacementValues, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(movdqa64load512_mask)(Address, ReplacementValues, Mask);
            }
        }
    }

    template<typename T> requires(sizeof(T) >= 4)
    INLINE constexpr Vector64<T> MaskLoadUnaligned(void* const Address, decltype(Mask<Vector64<T>>()) Mask, Vector64<T> ReplacementValues = Simd::SetAll<Vector64<T>>(0)) MIN_VECTOR_WIDTH(512)
    {
        if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(loadups512_mask)(Address, ReplacementValues, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(loadupd512_mask)(Address, ReplacementValues, Mask);
            }
        }
        else if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(loaddqusi512_mask)(Address, ReplacementValues, Mask);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(loaddqudi512_mask)(Address, ReplacementValues, Mask);
            }
        }
    }

#endif //AVX512

    template<typename TargetType, typename RegisterType> requires(NumElements<TargetType>() == NumElements<RegisterType>())
    INLINE constexpr TargetType ConvertVector(RegisterType Source)
    {
        return TargetType{__builtin_convertvector(Source, TargetType)};
    }


    template<int32_t I1, int32_t I2, int32_t I3, int32_t I4>
    INLINE consteval int32_t MakePermuteMask()
    {
        return (I1 << 0) | (I2 << 2) | (I3 << 4) | (I4 << 6);
    }

#ifdef AVX

    //shuffle elements in Source across lanes using Index
        template<int32_t... Index, typename T> requires(sizeof(T) == 4 && sizeof...(Index) == 4)
        INLINE constexpr Vector16<T> ShuffleCrossLane(Vector16<T> Source) MIN_VECTOR_WIDTH(128)
        {
            if constexpr(std::is_floating_point_v<T>)
            {
                return BUILTIN(vpermilps)(Source, MakePermuteMask<Index...>());
            }
            else if constexpr(std::is_integral_v<T>)
            {
                return BUILTIN(pshufd)(Source, MakePermuteMask<Index...>());
            }
        }

#endif //AVX
#ifdef AVX2

    //shuffle elements in Source across lanes using Index
    template<int32_t... Index, typename T> requires(sizeof(T) == 8 && sizeof...(Index) == 4)
    INLINE constexpr Vector32<T> ShuffleCrossLane(Vector32<T> Source) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(std::is_floating_point_v<T>)
        {
            return BUILTIN(permdf256)(Source, MakePermuteMask<Index...>());
        }
        else if constexpr(std::is_integral_v<T>)
        {
            return BUILTIN(permdi256)(Source, MakePermuteMask<Index...>());
        }
    }

    ///shuffle elements in Source within lanes using Control
    ///\param I0:I3 example 1, 1, 0, 1
    template<int32_t I0, int32_t I1, int32_t I2, int32_t I3, typename T> requires(sizeof(T) == 8)
    INLINE constexpr Vector32<T> ShuffleInLane(Vector32<T> Source) MIN_VECTOR_WIDTH(256)
    {
        return BUILTIN(vpermilpd256)(Source, (I0 << 0) | (I1 << 1) | (I2 << 2) | (I3 << 3));
    }

    template<typename T> requires(sizeof(T) == 8)
    INLINE constexpr Vector32<T> UnpackLow(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 0, 4 + 0, 2, 4 + 2);
    }

    template<typename T> requires(sizeof(T) == 4)
    INLINE constexpr Vector32<T> UnpackLow(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 0, 8+0, 1, 8+1, 4, 8 + 4, 5, 8+5);
    }

    template<typename T> requires(sizeof(T) == 2)
    INLINE constexpr Vector32<T> UnpackLow(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last,  0, 16+0, 1, 16+1, 2, 16+2, 3, 16+3, 8, 16+8, 9, 16+9, 10, 16+10, 11, 16+11);
    }

    template<typename T> requires(sizeof(T) == 1)
    INLINE constexpr Vector32<T> UnpackLow(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 0, 32+0, 1, 32+1, 2, 32+2, 3, 32+3, 4, 32+4, 5, 32+5, 6, 32+6, 7, 32+7, 16, 32+16, 17, 32+17, 18, 32+18, 19, 32+19, 20, 32+20, 21, 32+21, 22, 32+22, 23, 32+23);
    }

    template<typename T> requires(sizeof(T) == 8)
    INLINE constexpr Vector64<T> UnpackLow(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 0, 8, 0+2, 8+2, 0+4, 8+4, 0+6, 8+6);
    }

    template<typename T> requires(sizeof(T) == 4)
    INLINE constexpr Vector64<T> UnpackLow(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 0, 16, 1, 17, 0+4,  16+4, 1+4, 17+4, 0+8, 16+8, 1+8, 17+8, 0+12, 16+12, 1+12, 17+12);
    }

    template<typename T> requires(sizeof(T) == 2)
    INLINE constexpr Vector64<T> UnpackLow(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 0,  32+0,   1, 32+1,2,  32+2,   3, 32+3,8,  32+8,   9, 32+9,10, 32+10, 11, 32+11,16, 32+16, 17, 32+17,18, 32+18, 19, 32+19,24, 32+24, 25, 32+25,26, 32+26, 27, 32+27);
    }

    template<typename T> requires(sizeof(T) == 1)
    INLINE constexpr Vector64<T> UnpackLow(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 0,  64+0,   1, 64+1,2,  64+2,   3, 64+3,4,  64+4,   5, 64+5,6,  64+6,   7, 64+7,16, 64+16, 17, 64+17,18, 64+18, 19, 64+19,20, 64+20, 21, 64+21,22, 64+22, 23, 64+23,32, 64+32, 33, 64+33,34, 64+34, 35, 64+35,36, 64+36, 37, 64+37,38, 64+38, 39, 64+39,48, 64+48, 49, 64+49,50, 64+50, 51, 64+51,52, 64+52, 53, 64+53,54, 64+54, 55, 64+55);
    }

    template<typename T> requires(sizeof(T) == 8)
    INLINE constexpr Vector32<T> UnpackHigh(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 1, 4+1, 3, 4+3);
    }

    template<typename T> requires(sizeof(T) == 4)
    INLINE constexpr Vector32<T> UnpackHigh(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 2, 8+2, 3, 8+3, 6, 8+6, 7, 8+7);
    }

    template<typename T> requires(sizeof(T) == 2)
    INLINE constexpr Vector32<T> UnpackHigh(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 4, 16+4, 5, 16+5, 6, 16+6, 7, 16+7, 12, 16+12, 13, 16+13, 14, 16+14, 15, 16+15);
    }

    template<typename T> requires(sizeof(T) == 1)
    INLINE constexpr Vector32<T> UnpackHigh(Vector32<T> First, Vector32<T> Last) MIN_VECTOR_WIDTH(256)
    {
        return __builtin_shufflevector(First, Last, 8, 32+8, 9, 32+9, 10, 32+10, 11, 32+11, 12, 32+12, 13, 32+13, 14, 32+14, 15, 32+15, 24, 32+24, 25, 32+25, 26, 32+26, 27, 32+27, 28, 32+28, 29, 32+29, 30, 32+30, 31, 32+31);
    }

    template<typename T> requires(sizeof(T) == 8)
    INLINE constexpr Vector64<T> UnpackHigh(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 1, 9, 1+2, 9+2, 1+4, 9+4, 1+6, 9+6);
    }

    template<typename T> requires(sizeof(T) == 4)
    INLINE constexpr Vector64<T> UnpackHigh(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 2, 18, 3, 19, 2+4,  18+4, 3+4,  19+4,2+8,  18+8,  3+8, 19+8,2+12, 18+12, 3+12, 19+12);
    }

    template<typename T> requires(sizeof(T) == 2)
    INLINE constexpr Vector64<T> UnpackHigh(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 4, 32+4, 5, 32+5, 6, 32+6, 7, 32+7,12, 32+12, 13, 32+13,14, 32+14, 15, 32+15,20, 32+20, 21, 32+21,22, 32+22, 23, 32+23,28, 32+28, 29, 32+29,30, 32+30, 31, 32+31);
    }

    template<typename T> requires(sizeof(T) == 1)
    INLINE constexpr Vector64<T> UnpackHigh(Vector64<T> First, Vector64<T> Last) MIN_VECTOR_WIDTH(512)
    {
        return __builtin_shufflevector(First, Last, 8,  64+8,   9, 64+9,10, 64+10, 11, 64+11,12, 64+12, 13, 64+13,14, 64+14, 15, 64+15,24, 64+24, 25, 64+25,26, 64+26, 27, 64+27,28, 64+28, 29, 64+29,30, 64+30, 31, 64+31,40, 64+40, 41, 64+41,42, 64+42, 43, 64+43,44, 64+44, 45, 64+45,46, 64+46, 47, 64+47,56, 64+56, 57, 64+57,58, 64+58, 59, 64+59,60, 64+60, 61, 64+61,62, 64+62, 63, 64+63);
    }

#endif //AVX2
#ifdef AVX2

    template<uint8_t Control, typename T>
    INLINE constexpr Vector16<T> Extract(Vector32<T> Source)
    {
        if constexpr(std::is_floating_point_v<T> && sizeof(T) == 4)
        {
            return BUILTIN(vextractf128_ps256)(Source, Control);
        }
        else if constexpr(std::is_floating_point_v<T> && sizeof(T) == 8)
        {
            return BUILTIN(vextractf128_pd256)(Source, Control);
        }
        else if constexpr(std::is_integral_v<T>)
        {
            return BUILTIN(extract128i256)(Source, Control);
        }
    }

#endif //AVX2
#ifdef AVX

    /// LeftToMul * RightToMul + ToAdd
    template<typename T> requires(sizeof(T) >= 4)
    INLINE constexpr Vector16<T> FusedMultiplyAdd(Vector16<T> LeftToMul, Vector16<T> RightToMul, Vector16<T> ToAdd) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(vfmaddps)(LeftToMul, RightToMul, ToAdd);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(vfmaddpd)(LeftToMul, RightToMul, ToAdd);
        }
    }

#endif //AVX
#ifdef AVX2

    /// LeftToMul * RightToMul + ToAdd
    template<typename T> requires(sizeof(T) >= 4)
    INLINE constexpr Vector32<T> FusedMultiplyAdd(Vector32<T> LeftToMul, Vector32<T> RightToMul, Vector32<T> ToAdd) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(vfmaddps256)(LeftToMul, RightToMul, ToAdd);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(vfmaddpd256)(LeftToMul, RightToMul, ToAdd);
        }
    }

    /// LeftToMul * RightToMul - ToSub
    template<typename T> requires(std::is_signed_v<T>)
    INLINE constexpr Vector32<T> FusedMultiplySubtract(Vector32<T> LeftToMul, Vector32<T> RightToMul, Vector32<T> ToSub) MIN_VECTOR_WIDTH(256)
    {
        return FusedMultiplyAdd(LeftToMul, RightToMul, ToSub * SetAll<Vector32<T>>(-1));
    }

#endif //AVX2
#ifdef AVX

    template<typename T>
    INLINE constexpr Vector16<T> MakeFromGreater(Vector16<T> Left, Vector16<T> Right) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(std::is_signed_v<T>)
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pmaxsb128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pmaxsw128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxps)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pmaxsd128)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxpd)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pmaxsq128)(Left, Right);
#endif
                }
            }
        }
        else
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pmaxub128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pmaxuw128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxps)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pmaxud128)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxpd)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pmaxuq128)(Left, Right);
#endif
                }
            }
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T>
    INLINE constexpr Vector32<T> MakeFromGreater(Vector32<T> Left, Vector32<T> Right) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(std::is_signed_v<T>)
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pmaxsb256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pmaxsw256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxps)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pmaxsd256)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxpd256)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pmaxsq256)(Left, Right);
#endif
                }
            }
        }
        else
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pmaxub256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pmaxuw256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxps256)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pmaxud256)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(maxpd256)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pmaxuq256)(Left, Right);
#endif
                }
            }
        }
    }

#endif //AVX2
#ifdef AVX

    template<typename T>
    INLINE constexpr Vector16<T> MakeFromLesser(Vector16<T> Left, Vector16<T> Right) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(std::is_signed_v<T>)
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pminsb128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pminsw128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minps)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pminsd128)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minpd)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pminsq128)(Left, Right);
#endif
                }
            }
        }
        else
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pminub128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pminuw128)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minps)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pminud128)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minpd)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pminuq128)(Left, Right);
#endif
                }
            }
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T>
    INLINE constexpr Vector32<T> MakeFromLesser(Vector32<T> Left, Vector32<T> Right) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(std::is_signed_v<T>)
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pminsb256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pminsw256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minps)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pminsd256)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minpd256)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pminsq256)(Left, Right);
#endif
                }
            }
        }
        else
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pminub256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pminuw256)(Left, Right);
            }
            else if constexpr(sizeof(T) == 4)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minps256)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
                    return BUILTIN(pminud256)(Left, Right);
                }
            }
            else if constexpr(sizeof(T) == 8)
            {
                if constexpr(std::is_floating_point_v<T>)
                {
                    return BUILTIN(minpd256)(Left, Right);
                }
                else if constexpr(std::is_integral_v<T>)
                {
#ifdef AVX512
                    return BUILTIN(pminuq256)(Left, Right);
#endif
                }
            }
        }
    }

#endif //AVX2
#ifdef AVX

    template<typename T>
    INLINE constexpr void Clamp(Vector16<T>& Source, Vector16<T> Min, Vector16<T> Max) MIN_VECTOR_WIDTH(128)
    {
        Source = MakeFromGreater(Source, Min);
        Source = MakeFromLesser(Source, Max);
    }

#endif //AVX
#ifdef AVX2

    template<typename T>
    INLINE constexpr void Clamp(Vector32<T>& Source, Vector32<T> Min, Vector32<T> Max) MIN_VECTOR_WIDTH(256)
    {
        Source = MakeFromGreater(Source, Min);
        Source = MakeFromLesser(Source, Max);
    }

#endif //AVX2
#ifdef AVX

    template<typename T> requires(std::is_signed_v<T> && std::is_integral_v<T>)
    INLINE constexpr Vector16<T> Absolute(Vector16<T> Source) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(sizeof(T) == 1)
        {
            return BUILTIN(pabsb128)(Source);
        }
        else if constexpr(sizeof(T) == 2)
        {
            return BUILTIN(pabsw128)(Source);
        }
        else if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(pabsd128)(Source);
        }
        else if constexpr(sizeof(T) == 8)
        {
#ifdef AVX512
            return BUILTIN(pabsq128)(Source);
#endif
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T> requires(std::is_signed_v<T>)
    INLINE constexpr Vector32<T> Absolute(Vector32<T> Source) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(pabsb256)(Source);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(pabsw256)(Source);
            }
            else if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(pabsd256)(Source);
            }
            else if constexpr(sizeof(T) == 8)
            {
#ifdef AVX512
                return BUILTIN(pabsq256)(Source);
#endif
            }
        }
        else if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                constexpr int32x8 SignMask{Simd::SetAll<int32x8>(0b011111111111111111111111111111111)};

                int32x8 SourceAsInt{reinterpret_cast<int32x8>(Source)};
                SourceAsInt &= SignMask;

                return reinterpret_cast<float32x8>(SourceAsInt);
            }
            else if constexpr(sizeof(T) == 8)
            {
                constexpr int64x4 SignMask{Simd::SetAll<int64x4>(0b0111111111111111111111111111111111111111111111111111111111111111)};

                int64x4 SourceAsInt{reinterpret_cast<int64x4>(Source)};
                SourceAsInt &= SignMask;

                return reinterpret_cast<float64x4>(SourceAsInt);
            }
        }
    }

#endif //AVX2

    template<typename RegisterType>
    ATTRIBUTE(warn_unused_result, always_inline)
    inline constexpr RegisterType LoadUnaligned(const void* const Data)
    {
        struct ATTRIBUTE(packed, may_alias) FSource
        {
            RegisterType Register;
        };

        return reinterpret_cast<RegisterType>(reinterpret_cast<const FSource*>(Data)->Register);
    }

    template<typename RegisterType>
    ATTRIBUTE(warn_unused_result, always_inline)
    inline constexpr RegisterType LoadAligned(const void* const Data)
    {
        return *reinterpret_cast<const RegisterType*>(Data);
    }

    template<typename RegisterType>
    INLINE constexpr void StoreUnaligned(void* const Target, const RegisterType Data)
    {
        struct ATTRIBUTE(packed, may_alias) FSource
        {
            RegisterType Register;
        };

        reinterpret_cast<FSource*>(Target)->Register = Data;
    }

    template<typename RegisterType>
    INLINE constexpr void StoreAligned(void* Target, const RegisterType Data)
    {
        *reinterpret_cast<RegisterType*>(Target) = Data;
    }

#ifdef AVX

    template<typename T> requires(sizeof(T) == 4 || sizeof(T) == 8)
    INLINE constexpr void MaskStore(Vector16<T>* Target, const Vector16<T> Mask, const Vector16<T> Data) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                BUILTIN(maskstored)(Target, Mask, Data);
            }
            else if constexpr(sizeof(T) == 8)
            {
                BUILTIN(maskstoreq)(Target, Mask, Data);
            }
        }
        else if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                BUILTIN(maskstoreps)(Target, Mask, Data);
            }
            else if constexpr(sizeof(T) == 8)
            {
                BUILTIN(maskstorepd)(Target, Mask, Data);
            }
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T> requires(sizeof(T) == 4 || sizeof(T) == 8)
    INLINE constexpr void MaskStore(Vector32<T>* Target, const Vector32<T> Mask, const Vector32<T> Data) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                BUILTIN(maskstored256)(Target, Mask, Data);
            }
            else if constexpr(sizeof(T) == 8)
            {
                BUILTIN(maskstoreq256)(Target, Mask, Data);
            }
        }
        else if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                BUILTIN(maskstoreps256)(Target, Mask, Data);
            }
            else if constexpr(sizeof(T) == 8)
            {
                BUILTIN(maskstorepd256)(Target, Mask, Data);
            }
        }
    }

#endif //AVX2
#ifdef AVX512

    template<typename T> requires(sizeof(T) == 4 || sizeof(T) == 8)
        INLINE constexpr void MaskStoreAligned(Vector64<T>* Target, const decltype(Mask<Vector64<T>>()) Mask, const Vector64<T> Data) MIN_VECTOR_WIDTH(512)
        {
            //for some reason Data and Mask has swapped argument positions
            if constexpr(std::is_integral_v<T>)
            {
                if constexpr(sizeof(T) == 4)
                {
                    BUILTIN(movdqa32store512_mask)(Target, Data, Mask);
                }
                else if constexpr(sizeof(T) == 8)
                {
                    BUILTIN(movdqa64store512_mask)(Target, Data, Mask);
                }
            }
            else if constexpr(std::is_floating_point_v<T>)
            {
                if constexpr(sizeof(T) == 4)
                {
                    BUILTIN(storeaps512_mask)(Target, Data, Mask);
                }
                else if constexpr(sizeof(T) == 8)
                {
                    BUILTIN(storeapd512_mask)(Target, Data, Mask);
                }
            }
        }

        template<typename T>
        INLINE constexpr void MaskStoreUnaligned(T* Target, const decltype(Mask<Vector64<T>>()) Mask, const Vector64<T> Data) MIN_VECTOR_WIDTH(512)
        {
            //for some reason Data and Mask has swapped argument positions
            if constexpr(std::is_integral_v<T>)
            {
                if constexpr(sizeof(T) == 1)
                {
                    BUILTIN(storedquqi512_mask)(Target, Data, Mask);
                }
                if constexpr(sizeof(T) == 2)
                {
                    BUILTIN(storedquhi512_mask)(Target, Data, Mask);
                }
                else if constexpr(sizeof(T) == 4)
                {
                    BUILTIN(storedqusi512_mask)(Target, Data, Mask);
                }
                else if constexpr(sizeof(T) == 8)
                {
                    BUILTIN(storedqudi512_mask)(Target, Data, Mask);
                }
            }
            else if constexpr(std::is_floating_point_v<T>)
            {
                if constexpr(sizeof(T) == 4)
                {
                    BUILTIN(storeups512_mask)(Target, Data, Mask);
                }
                else if constexpr(sizeof(T) == 8)
                {
                    BUILTIN(storeupd512_mask)(Target, Data, Mask);
                }
            }
        }

#endif //AVX512
#ifdef AVX

    template<typename T> requires std::is_floating_point_v<T>
    INLINE constexpr Vector16<T> SquareRoot(Vector16<T> Source) MIN_VECTOR_WIDTH(128)
    {
        if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(sqrtps)(Source);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(sqrtpd)(Source);
        }
    }

#endif //AVX
#ifdef AVX2

    template<typename T> requires std::is_floating_point_v<T>
    INLINE constexpr Vector32<T> SquareRoot(Vector32<T> Source) MIN_VECTOR_WIDTH(256)
    {
        if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(sqrtps256)(Source);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(sqrtpd256)(Source);
        }
    }

#endif //AVX2
#ifdef AVX512

    template<typename T> requires std::is_floating_point_v<T>
    INLINE constexpr Vector64<T> SquareRoot(Vector64<T> Source) MIN_VECTOR_WIDTH(512)
    {
        if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(sqrtps512)(Source);
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(sqrtpd512)(Source);
        }
    }

#endif //AVX512

    template<typename Vector, int32_t... Control>
    concept ValidControlIndices = (sizeof...(Control) == NumElements<Vector>()) && ((Control == 0 || Control == 1) && ...);

    template<typename RetType, int32_t... I>
    inline consteval RetType MakeSelectionMask()
    {
        int64_t Shift{-1};
        return ((I << (++Shift)) | ...);
    }

    static_assert(MakeSelectionMask<int32_t, 0, 1, 0, 1>() == ((0 << 0) | (1 << 1) | (0 << 2) | (1 << 3)));

#ifdef AVX

    ///
    /// \tparam Control a 0 at index N means that the N element of SourceOne will be used, a 1 at index N means that the N element of SourceTwo will be used.
    /// \param SourceOne
    /// \param SourceTwo
    /// \return the combined vector
    template<int32_t... Control, typename T> requires(sizeof(T) >= 2 && ValidControlIndices<Vector16<T>, Control...>)
    INLINE constexpr Vector16<T> SelectElements(Vector16<T> SourceOne, Vector16<T> SourceTwo)
    {
        if constexpr(sizeof(T) == 2)
        {
            return BUILTIN(pblendw128)(SourceOne, SourceTwo, MakeSelectionMask<int32_t, Control...>());
        }
        else if constexpr(sizeof(T) == 4)
        {
            return BUILTIN(blendps)(SourceOne, SourceTwo, MakeSelectionMask<int32_t, Control...>());
        }
        else if constexpr(sizeof(T) == 8)
        {
            return BUILTIN(blendpd)(SourceOne, SourceTwo, MakeSelectionMask<int32_t, Control...>());
        }
    }

#endif
#ifdef AVX2

    ///
    /// \tparam Control a 0 at index N means that the N element of SourceOne will be used, a 1 at index N means that the N element of SourceTwo will be used
    /// \param SourceOne
    /// \param SourceTwo
    /// \return the combined vector
    template<int32_t... Control, typename T> requires(sizeof(T) == 8 && ValidControlIndices<Vector32<T>, Control...>)
    INLINE constexpr Vector32<T> SelectElements(Vector32<T> SourceOne, Vector32<T> SourceTwo)
    {
        return BUILTIN(blendpd256)(SourceOne, SourceTwo, MakeSelectionMask<int32_t, Control...>());
    }

    ///
    /// \tparam Control a 0 at index N means that the N element of SourceOne will be used, a 1 at index N means that the N element of SourceTwo will be used    /// \param SourceOne
    /// \param SourceTwo
    /// \return the combined vector
    template<int32_t... Control, typename T> requires(sizeof(T) == 4 && ValidControlIndices<Vector32<T>, Control...>)
    INLINE constexpr Vector32<T> SelectElements(Vector32<T> SourceOne, Vector32<T> SourceTwo)
    {
        return BUILTIN(blendps256)(SourceOne, SourceTwo, MakeSelectionMask<int32_t, Control...>());
    }

    ///
    /// \tparam Control a 0 at index N means that the N element of SourceOne will be used, a 1 at index N means that the N element of SourceTwo will be used
    /// \param SourceOne
    /// \param SourceTwo
    /// \return the combined vector
    template<int32_t... Control, typename T> requires(sizeof(T) == 2 && ValidControlIndices<Vector32<T>, Control...>)
    INLINE constexpr Vector32<T> SelectElements(Vector32<T> SourceOne, Vector32<T> SourceTwo)
    {
        return BUILTIN(blendw256)(SourceOne, SourceTwo, MakeSelectionMask<int32_t, Control...>());
    }

    template<int32_t OffsetScale> requires(OffsetScale == 1 || OffsetScale == 2 || OffsetScale == 4 || OffsetScale == 8)
    INLINE constexpr int64x4 Gather(const void* __restrict BaseAddress, int32x4 Offsets, int64x4 ConditionalLoadMask = {-1, -1, -1, -1}, int64x4 SourceIfMaskNotSet = BUILTIN(undef256)())
    {
        return BUILTIN(gatherd_q256)(SourceIfMaskNotSet, static_cast<const long long*>(BaseAddress), Offsets, ConditionalLoadMask, OffsetScale);
    }

#endif
#ifdef AVX512

    ///
    /// \tparam Control a 0 at index N means that the N element of SourceOne will be used, a 1 at index N means that the N element of SourceTwo will be used
    /// \param SourceOne
    /// \param SourceTwo
    /// \return the combined vector
    template<int32_t... Control, typename T> requires(ValidControlIndices<Vector64<T>, Control...>)
    INLINE Vector64<T> SelectElements(Vector64<T> SourceOne, Vector64<T> SourceTwo)
    {
        if constexpr(std::is_integral_v<T>)
        {
            if constexpr(sizeof(T) == 1)
            {
                return BUILTIN(selectb_512)(MakeSelectionMask<uint64_t, Control...>(), SourceOne, SourceTwo);
            }
            else if constexpr(sizeof(T) == 2)
            {
                return BUILTIN(selectw_512)(MakeSelectionMask<uint32_t, Control...>(), SourceOne, SourceTwo);
            }
            else if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(selectd_512)(MakeSelectionMask<uint16_t, Control...>(), SourceOne, SourceTwo);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(selectq_512)(MakeSelectionMask<uint8_t, Control...>(), SourceOne, SourceTwo);
            }
        }
        else if constexpr(std::is_floating_point_v<T>)
        {
            if constexpr(sizeof(T) == 4)
            {
                return BUILTIN(selectps_512)(MakeSelectionMask<uint16_t, Control...>(), SourceOne, SourceTwo);
            }
            else if constexpr(sizeof(T) == 8)
            {
                return BUILTIN(selectpd_512)(MakeSelectionMask<uint8_t, Control...>(), SourceOne, SourceTwo);
            }
        }
    }

#endif

    INLINE int64x4 NextAlignedAddress(int64x4 Addresses, int64x4 Align)
    {
        Align -= 1;
        return (Addresses + Align) & ~Align;
    }

    INLINE int64x8 NextAlignedAddress(int64x8 Addresses, int64x8 Align)
    {
        Align -= 1;
        return (Addresses + Align) & ~Align;
    }

    /*
     * copies and moves the elements  in the Source by ShuffleAmount to the left
     * ShuffleLeft({0, 1, 1, 0, 1, 0, 1, 1}, 3) == {0, 1, 0, 1, 1, 0, 0, 0}
     */
    template<typename RegisterType, typename ElementType = ElementType<RegisterType>>
    INLINE RegisterType ShuffleLeft(RegisterType Source, const int32_t ShuffleAmount)
    {
        static constexpr uint64_t NumElements{Simd::NumElements<RegisterType>()};
        static constexpr uint64_t StackSize{sizeof(ElementType) * NumElements * 3};

        ElementType* StackBuffer{static_cast<ElementType*>(__builtin_alloca(StackSize))};
        __builtin_memset(StackBuffer, 0, StackSize);

        StoreUnaligned(&StackBuffer[NumElements], Source);
        return LoadUnaligned<RegisterType>(&StackBuffer[NumElements - ShuffleAmount]);
    }

    /*
     * copies and moves the elements  in the Source by ShuffleAmount to the right
     * ShuffleRight({0, 1, 1, 0, 1, 0, 1, 1}, 3) == {0, 0, 0, 0, 1, 1, 0, 1}
     */
    template<typename RegisterType>
    INLINE RegisterType ShuffleRight(RegisterType Source, const int32_t ShuffleAmount)
    {
        return ShuffleLeft(Source, ShuffleAmount * -1);
    }

    template<typename T>
    INLINE T* ToPtr(Vector16<T>* Source)
    {
        return reinterpret_cast<T*>(ASSUME_ALIGNED(Source, 16));
    }

    template<typename T>
    INLINE T* ToPtr(Vector32<T>* Source)
    {
        return reinterpret_cast<T*>(ASSUME_ALIGNED(Source, 32));
    }

    template<typename T>
    INLINE T* ToPtr(Vector64<T>* Source)
    {
        return reinterpret_cast<T*>(ASSUME_ALIGNED(Source, 64));
    }

    template<typename T>
    INLINE const T* ToPtr(const Vector16<T>* Source)
    {
        return reinterpret_cast<const T*>(ASSUME_ALIGNED(Source, 16));
    }

    template<typename T>
    INLINE const T* ToPtr(const Vector32<T>* Source)
    {
        return reinterpret_cast<const T*>(ASSUME_ALIGNED(Source, 32));
    }

    template<typename T>
    INLINE const T* ToPtr(const Vector64<T>* Source)
    {
        return reinterpret_cast<const T*>(ASSUME_ALIGNED(Source, 64));
    }
} //namespace Simd

#ifdef AVX

inline consteval char8x16 operator""_char8_16(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<char8x16>(Value);
}

inline consteval int8x16 operator""_int8_16(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<int8x16>(Value);
}

inline consteval uint8x16 operator""_uint8_16(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<uint8x16>(Value);
}

inline consteval int16x8 operator"" _int16_8(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<int16x8>(Value);
}

inline consteval uint16x8 operator""_uint16_8(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<uint16x8>(Value);
}

inline consteval int32x4 operator""_int32_4(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<int32x4>(Value);
}

inline consteval uint32x4 operator""_uint32_4(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<uint32x4>(Value);
}

inline consteval int64x2 operator""_int64_2(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<int64x2>(Value);
}

inline consteval uint64x2 operator""_uint64_2(unsigned long long Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<uint64x2>(Value);
}

inline consteval float32x4 operator""_float32_4(long double Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<float32x4>(Value);
}

inline consteval float64x2 operator""_float64_2(long double Value) MIN_VECTOR_WIDTH(128)
{
    return Simd::SetAll<float64x2>(Value);
}

#endif //AVX
#ifdef AVX2

inline consteval char8x32 operator""_char8_32(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<char8x32>(Value);
}

inline consteval int8x32 operator""_int8_32(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<int8x32>(Value);
}

inline consteval uint8x32 operator""_uint8_32(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<uint8x32>(Value);
}

inline consteval int16x16 operator""_int16_16(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<int16x16>(Value);
}

inline consteval uint16x16 operator""_uint16_16(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<uint16x16>(Value);
}

inline consteval int32x8 operator""_int32_8(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<int32x8>(Value);
}

inline consteval uint32x8 operator""_uint32_8(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<uint32x8>(Value);
}

inline consteval int64x4 operator""_int64_4(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<int64x4>(Value);
}

inline consteval uint64x4 operator""_uint64_4(unsigned long long Value) MIN_VECTOR_WIDTH(256)
{
    return Simd::SetAll<uint64x4>(Value);
}

#endif //AVX2
#ifdef AVX512

inline consteval char8x64 operator""_char8_64(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<char8x64>(Value);
}

inline consteval int8x64 operator""_int8_64(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<int8x64>(Value);
}

inline consteval uint8x64 operator""_uint8_64(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<uint8x64>(Value);
}

inline consteval int16x32 operator""_int16_32(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<int16x32>(Value);
}

inline consteval uint16x32 operator""_uint16_32(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<uint16x32>(Value);
}

inline consteval int32x16 operator""_int32_16(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<int32x16>(Value);
}

inline consteval uint32x16 operator""_uint32_16(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<uint32x16>(Value);
}

inline consteval int64x8 operator""_int64_8(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<int64x8>(Value);
}

inline consteval uint64x8 operator""_uint64_8(unsigned long long Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<uint64x8>(Value);
}

inline consteval float32x16 operator""_float32_16(long double Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<float32x16>(Value);
}

inline consteval float64x8 operator""_float64_8(long double Value) MIN_VECTOR_WIDTH(512)
{
    return Simd::SetAll<float64x8>(Value);
}

#endif //AVX512

