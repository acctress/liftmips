#pragma once

#include <liftmips/decoder.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <format>

namespace liftmips::translator
{
    using namespace liftmips::decoder;

    inline std::unordered_map< opcode_t, std::string_view > opcode_mnemonics {
        { opcode_t::ADDU, "iadd" },
        { opcode_t::SUBU, "isub" },
    };

    struct lift_context_t
    {
        std::array< std::string, 32 > reg_identifiers;
        std::uint32_t                 next_value_id;
        std::string                   ir;

        lift_context_t( ) : next_value_id( 32 )
        {
            for ( auto i { 0uz }; i < 32u; ++i )
                reg_identifiers[ i ] = "%" + std::to_string( i );
        }
    };

    inline std::string alloc_value( lift_context_t& ctx )
    {
        return "%" + std::to_string( ctx.next_value_id++ );
    }

    using lift_fn_t = void( * )( const instr_t&, lift_context_t& );

    inline void lift_rrr( const instr_t& instr, lift_context_t& ctx )
    {
        const auto& src1 = ctx.reg_identifiers[ instr.rs ];
        const auto& src2 = ctx.reg_identifiers[ instr.rt ];
        const auto& inst = opcode_mnemonics.at( instr.op );

        auto val = alloc_value( ctx );

        const auto line = std::format( "{} = {} {}, {}\n", val, inst, src1, src2 );
        ctx.reg_identifiers[ instr.rd ] = val;
        ctx.ir += line;
    }

    inline void lift_instr( const instr_t& instr, lift_context_t& ctx )
    {
        lift_rrr( instr, ctx );
    }
}