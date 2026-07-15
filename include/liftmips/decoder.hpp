#pragma once

#include <cstdint>
#include <unordered_map>

namespace liftmips::decoder
{
    enum class opcode_t : std::uint8_t
    {
        ADDU,
    };

    struct instr_t
    {
        opcode_t        op;             /* opcode */
        std::uint8_t    rs, rt, rd;     /* register source, register target, register destination */
        std::int32_t    imm;            /* immediate */
        std::uint8_t    shamt;          /* shift amount */
        std::uint32_t   target;         /* jump destination */
    };

    inline std::unordered_map< std::uint32_t, opcode_t > opcode_table {
        { 0x21, opcode_t::ADDU },
    };

    constexpr std::uint32_t extract_bits( const std::uint32_t word, const int high, const int low )
    {
        const auto width = high - low + 1;
        const auto mask = (1 << width) - 1;
        return word >> low & mask;
    }

    inline auto decode_r_type( const std::uint32_t word ) -> instr_t
    {
        const auto rs    = extract_bits( word, 25, 21 );
        const auto rt    = extract_bits( word, 20, 16 );
        const auto rd    = extract_bits( word, 15, 11 );
        const auto shamt = extract_bits( word, 10, 6  );
        const auto funct = extract_bits( word, 5, 0   );

        instr_t result { };
        result.op = opcode_table.at( funct );   /* .at throws so do we handle this now or laterrr??? later. */
        result.rs = rs;
        result.rt = rt;
        result.rd = rd;
        result.shamt = shamt;

        return result;
    }
}