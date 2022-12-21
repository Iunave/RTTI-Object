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

#if !defined(__AVX2__)
#error "this library requires AVX2 to function"
#endif

#include <tuple>
#include <string_view>
#include <array>

#if !NDEBUG
#include <cassert>
#endif

#include "SIMD_lib/simd.hpp"

#if !defined(ARGS_CASE) && !defined(MULTIPLE_ARGS_CASE) && !defined(PP_NARG_) && !defined(PP_ARG_N) && !defined(NUM_ARGUMENTS)

#define ARGS_CASE(...) 0
#define MULTIPLE_ARGS_CASE(...) PP_NARG_(__VA_ARGS__,PP_RSEQ_N())

#define PP_NARG_(...) PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(_1,_2,_3,_4,_5,_6, _7,_8,_9,_10,_11,_12,_13,_14,_15,_16,_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60, _61,_62,_63,N,...) N
#define PP_RSEQ_N() 63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0

#define NUM_ARGUMENTS(...) __VA_OPT__(MULTIPLE_)##ARGS_CASE(__VA_ARGS__)

#endif

#define RTTI_DECLARE_CLASS(Class)\
class Class

#define RTTI_SPECIALIZE_TYPE_TRAIT(Class)\
template<>\
struct ::Rtti::TIsObjectClass<Class>\
{\
    static constexpr bool Value = true;\
};

#define RTTI_SPECIALIZE_INFO(Class)\
template<>\
struct ::Rtti::TObjectInfo<Class>\
{\
    inline static constexpr std::string_view Name = #Class;\
    inline static constexpr uint16_t TypeID = __COUNTER__;\
};

/*
 * The arguments for the RTTI_OBJECT_CLASS macro is the class name
 *
 * RTTI_OBJECT_CLASS(OMyClass)
 * class OMyClass : public OObject, public IObject, public NotAnObject
 * {
 *     RTTI_OBJECT_BASES(OObject, IObject)
 * };
 */
#define RTTI_OBJECT_CLASS(Class)\
RTTI_DECLARE_CLASS(Class);\
RTTI_SPECIALIZE_TYPE_TRAIT(Class)\
RTTI_SPECIALIZE_INFO(Class)

/*
 * The arguments for the RTTI_OBJECT_CLASS_NAMESPACED(...) macro is the namespace and class name
 *
 * RTTI_OBJECT_CLASS_NAMESPACED(Namespace, OMyClass)
 * class Namespace::OMyClass : public OObject1, public OObject2, public NotAnObject
 * {
 *   RTTI_OBJECT_BASES(OObject1, OObject2)
 * };
 */
#define RTTI_OBJECT_CLASS_NAMESPACED(Namespace, Class)\
namespace Namespace\
{\
RTTI_DECLARE_CLASS(Class);\
}\
RTTI_SPECIALIZE_TYPE_TRAIT(Namespace::Class)\
RTTI_SPECIALIZE_INFO(Namespace::Class)

/*
 * The arguments for the RTTI_OBJECT_BASES(...) macro is all the direct base classes (if they are objects themselves)
 *
 * RTTI_OBJECT_CLASS(OMyClass)
 * class OMyClass : public OObject1, public OObject2, public NotAnObject
 * {
 *     RTTI_OBJECT_BASES(OObject1, OObject2)
 * };
 */
#define RTTI_OBJECT_BASES(...)\
public:\
\
static constexpr Rtti::AddPointersToTupleArgs<__VA_ARGS__> GetDirectBaseClasses()\
{\
    return {};\
}\
\
static constexpr uint64_t NumDirectBaseClasses()\
{\
    return NUM_ARGUMENTS(__VA_ARGS__);\
}\
\
static constexpr uint64_t NumTotalBaseClasses()\
{\
    auto FoldNumTotalBaseClasses = []<typename... Ts>()\
    {\
        return (0 + ... + Ts::NumTotalBaseClasses());\
    };\
\
    return NumDirectBaseClasses() + FoldNumTotalBaseClasses.template operator()<__VA_ARGS__>();\
}\
\
virtual int64_t OffsetThisFromID(uint16_t TargetID) const __VA_OPT__(override)\
{\
    using ThisType = std::remove_cv_t<std::remove_pointer_t<decltype(this)>>;\
    return Rtti::OffsetFromID<ThisType>(reinterpret_cast<const int64_t>(this), TargetID);\
}\
\
virtual uint16_t GetObjectID() const __VA_OPT__(override)\
{\
    using ThisType = std::remove_cv_t<std::remove_pointer_t<decltype(this)>>;\
    return Rtti::TObjectInfo<ThisType>::TypeID;\
}\
\
virtual std::string_view GetObjectName() const __VA_OPT__(override)\
{\
    using ThisType = std::remove_cv_t<std::remove_pointer_t<decltype(this)>>;\
    return Rtti::TObjectInfo<ThisType>::Name;\
}\
\
private:

namespace
{
    auto expand_counter = [](){__COUNTER__;}; //make counter 1
}

namespace Rtti
{
    template<typename Class>
    struct TObjectInfo;

    template<typename Class>
    struct TIsObjectClass
    {
        inline static constexpr bool Value = false;
    };

    template<typename Class>
    concept IsObjectClass = TIsObjectClass<std::remove_cvref_t<Class>>::Value;

    template<typename... VarArgs>
    using AddPointersToTupleArgs = std::tuple<VarArgs*...>;

    template<typename Derived, uint64_t Index>
    using BaseClassAt = std::remove_pointer_t<std::remove_cvref_t<decltype(std::get<Index>(Derived::GetDirectBaseClasses()))>>;
    
    template<typename Class>
    using OffsetAndIDArrayType = std::array<uint32_t, Class::NumTotalBaseClasses() + 1>;

    template<typename From, typename To>
    inline consteval int64_t PointerOffset()
    {
        constexpr const From* Type_this = __builtin_constant_p(reinterpret_cast<const From*>(sizeof(From)))
                                          ? reinterpret_cast<const From*>(sizeof(From))
                                          : reinterpret_cast<const From*>(sizeof(From));

        constexpr const To* Base_this = static_cast<const To*>(Type_this);

        constexpr const uint8_t* Type_this_bytes = __builtin_constant_p(reinterpret_cast<const uint8_t*>(Type_this))
                                                   ? reinterpret_cast<const uint8_t*>(Type_this)
                                                   : reinterpret_cast<const uint8_t*>(Type_this);

        constexpr const uint8_t* Base_this_bytes = __builtin_constant_p(reinterpret_cast<const uint8_t*>(Base_this))
                                                   ? reinterpret_cast<const uint8_t*>(Base_this)
                                                   : reinterpret_cast<const uint8_t*>(Base_this);

        constexpr const int64_t Base_offset = Base_this_bytes - Type_this_bytes;

        return Base_offset;
    }

    template<typename T, uint64_t... I>
    inline consteval std::array<T, (I + ...)> JoinArrays(const std::array<T, I>&... Arrays)
    {
        std::array<T, (I + ...)> ResultArray;
        T* ResultBegin = ResultArray.Data();

        ((__builtin_memcpy(ResultBegin, Arrays.Data(), I * sizeof(T)), ResultBegin += I), ...);

        return ResultArray;
    }

    template<typename Derived, typename Class>
    inline consteval OffsetAndIDArrayType<Class> MakeOffsetAndIDArray()
    {
        int16_t Offset = static_cast<int16_t>(PointerOffset<Derived, Class>());

        std::array<uint32_t, 1> OffsetAndTypeID{(uint32_t(Offset) << 16) | uint32_t(TObjectInfo<Class>::TypeID)}; //push offset to the upper half and combine with typeID in the lower half

        if constexpr(constexpr uint64_t NumDirectBaseClasses = Class::NumDirectBaseClasses(); NumDirectBaseClasses > 0)
        {
            auto ExpandTuple = [&OffsetAndTypeID]<std::size_t... I>(std::index_sequence<I...>)
            {
                return JoinArrays(OffsetAndTypeID, MakeOffsetAndIDArray<Derived, BaseClassAt<Class, I>>()...);
            };

            return ExpandTuple(std::make_index_sequence<NumDirectBaseClasses>{});
        }
        else
        {
            return OffsetAndTypeID;
        }
    }

#if defined(__AVX512__)

    template<typename Class>
    inline int64_t OffsetFromID(const int64_t SourcePtr, uint16_t TargetID)
    {
        static constexpr OffsetAndIDArrayType<Class> OffsetAndIDArray alignas(uint32x16){MakeOffsetAndIDArray<Class, Class>()};
        static_assert(OffsetAndIDArray.size() <= 64, "64 ID,s is the limit");

        const uint32x16 TargetIDVector = Simd::SetAll<uint32x16>(TargetID);

        uint64_t MatchIndex{0};
        int64_t Index{0};

        #pragma unroll
        while(Index <= (int64_t{OffsetAndIDArray.size()} - 16))
        {
            uint32x16 StoredIDs = Simd::LoadAligned<uint32x16>(OffsetAndIDArray.data() + Index);
            StoredIDs &= 0x0000FFFF; //mask out the offset part

            uint64_t Mask = static_cast<uint64_t>(Simd::MoveMask(StoredIDs == TargetIDVector));
            Mask <<= Index;
            MatchIndex |= Mask;

            Index += 16;
        }

        constexpr uint64_t RemainingElements = OffsetAndIDArray.size() % 16;

        if constexpr(RemainingElements > 0)
        {
            uint64_t ValidMask = (~0ULL) >> ((64 - Index) - RemainingElements);

            uint32x16 StoredIDs = Simd::LoadAligned<uint32x16>(OffsetAndIDArray.data() + Index);
            StoredIDs &= 0x0000FFFF; //mask out the offset part

            uint64_t Mask = static_cast<uint64_t>(Simd::MoveMask(StoredIDs == TargetIDVector));
            Mask <<= Index;

            MatchIndex |= Mask;
            MatchIndex &= ValidMask;
        }

        if(MatchIndex != 0)
        {
            MatchIndex = __builtin_ffsll(MatchIndex) - 1;

            uint32_t MatchedElement = OffsetAndIDArray[MatchIndex];
            int16_t Offset = static_cast<int16_t>(MatchedElement >> 16); //push the offset to the low 16 bits

            return SourcePtr + Offset;
        }
        else
        {
            return 0;
        }
    }

#elif defined(__AVX2__)

    template<typename Class>
    inline int64_t OffsetFromID(const int64_t SourcePtr, uint16_t TargetID)
    {
        static constexpr OffsetAndIDArrayType<Class> OffsetAndIDArray alignas(uint32x8) = MakeOffsetAndIDArray<Class, Class>();
        static_assert(OffsetAndIDArray.size() <= 64, "64 ID,s is the limit");

        const uint32x8 TargetIDVector = Simd::SetAll<uint32x8>(TargetID);

        uint64_t MatchIndex = 0;
        int64_t Index = 0;

        #pragma unroll
        while(Index <= (int64_t{OffsetAndIDArray.size()} - 8))
        {
            uint32x8 StoredIDs = Simd::LoadAligned<uint32x8>(OffsetAndIDArray.data() + Index);
            StoredIDs &= 0x0000FFFF; //mask out the offset part

            uint64_t Mask = static_cast<uint64_t>(Simd::MoveMask(StoredIDs == TargetIDVector));
            Mask <<= Index;

            MatchIndex |= Mask;

            Index += 8;
        }

        if constexpr(constexpr uint64_t RemainingElements = OffsetAndIDArray.size() % 8; RemainingElements > 0)
        {
            const uint64_t ValidMask = (~0ULL) >> ((64 - Index) - RemainingElements);

            uint32x8 StoredIDs = Simd::LoadAligned<uint32x8>(OffsetAndIDArray.data() + Index);
            StoredIDs &= 0x0000FFFF; //mask out the offset part

            uint64_t Mask = static_cast<uint64_t>(Simd::MoveMask(StoredIDs == TargetIDVector));
            Mask <<= Index;

            MatchIndex |= Mask;
            MatchIndex &= ValidMask;
        }

        if(MatchIndex != 0)
        {
            MatchIndex = __builtin_ffsll(MatchIndex) - 1;

            uint32_t MatchedElement = OffsetAndIDArray[MatchIndex];
            int16_t Offset = static_cast<int16_t>(MatchedElement >> 16); //push the offset to the low 16 bits

            return SourcePtr + Offset;
        }
        else
        {
            return 0;
        }
    }

#endif

} //namespace Rtti

template<typename TargetType, typename BaseType> requires(Rtti::IsObjectClass<std::remove_pointer_t<TargetType>> && Rtti::IsObjectClass<BaseType>)
inline TargetType ObjectCast(BaseType* BasePointer)
{
    using TargetTypeClass = std::remove_cv_t<std::remove_pointer_t<TargetType>>;

    if(BasePointer != nullptr)
    {
        if constexpr(std::is_base_of_v<TargetTypeClass, std::remove_cv_t<BaseType>>)
        {
            return static_cast<TargetType>(BasePointer);
        }
        else
        {
            constexpr uint16_t TargetID = Rtti::TObjectInfo<TargetTypeClass>::TypeID;
            return reinterpret_cast<TargetType>(BasePointer->OffsetThisFromID(TargetID));
        }
    }

    return nullptr;
}

template<typename TargetType, typename BaseType> requires(Rtti::IsObjectClass<std::remove_pointer_t<TargetType>> && Rtti::IsObjectClass<BaseType>)
inline TargetType ObjectCastExact(BaseType* BasePointer)
{
    using TargetTypeClass = std::remove_cv_t<std::remove_pointer_t<TargetType>>;

    if(BasePointer != nullptr)
    {
        constexpr uint16_t TargetID = Rtti::TObjectInfo<TargetTypeClass>::GetObjectTypeID();

        if(BasePointer->GetObjectID() == TargetID)
        {
            return static_cast<TargetType>(BasePointer);
        }
    }

    return nullptr;
}

template<typename TargetType, typename BaseType> requires(Rtti::IsObjectClass<std::remove_pointer_t<TargetType>> && Rtti::IsObjectClass<BaseType>)
inline TargetType ObjectCastChecked(BaseType* BasePointer)
{
    using TargetTypeClass = std::remove_cv_t<std::remove_pointer_t<TargetType>>;

#if !NDEBUG
    assert(BasePointer != nullptr);
#endif

    if constexpr(static_cast<TargetType>(BasePointer))
    {
#if !NDEBUG
        constexpr uint16_t TargetID = Rtti::TObjectInfo<TargetTypeClass>::TypeID;
        assert(BasePointer->OffsetThisFromID(TargetID) != nullptr);
#endif
        return static_cast<TargetType>(BasePointer);
    }
    else
    {
        constexpr uint16_t TargetID = Rtti::TObjectInfo<TargetTypeClass>::TypeID;
        return reinterpret_cast<TargetType>(BasePointer->OffsetThisFromID(TargetID));
    }
}

RTTI_OBJECT_CLASS(RttiObject)
class RttiObject
{
RTTI_OBJECT_BASES()
public:

    RttiObject() = default;
    virtual ~RttiObject() = default;
};


