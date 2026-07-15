#pragma once

#include <liftmips/decoder.hpp>
#include <unordered_map>
#include <string>
#include <array>
#include <format>

namespace liftmips::translator
{
    using namespace liftmips::decoder;

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

    inline void lift_addu( const instr_t& instr, lift_context_t& ctx )
    {
        auto src1 = ctx.reg_identifiers[ instr.rs ];
        auto src2 = ctx.reg_identifiers[ instr.rt ];
        auto val = alloc_value( ctx );
        const auto line = std::format( "{} = iadd {}, {}\n", val, src1, src2 );
        ctx.reg_identifiers[ instr.rd ] = val;
        ctx.ir += line;
    }

    inline void lift_subu( const instr_t& instr, lift_context_t& ctx )
    {
        auto src1 = ctx.reg_identifiers[ instr.rs ];
        auto src2 = ctx.reg_identifiers[ instr.rt ];
        auto val = alloc_value( ctx );
        const auto line = std::format( "{} = isub {}, {}\n", val, src1, src2 );
        ctx.reg_identifiers[ instr.rd ] = val;
        ctx.ir += line;
    }

    inline std::unordered_map< opcode_t, lift_fn_t > lift_table {
        { opcode_t::ADDU, lift_addu },
        { opcode_t::SUBU, lift_subu },
    };

    inline void lift_instr( const instr_t& instr, lift_context_t& ctx )
    {
        lift_table.at( instr.op )( instr, ctx );
    }
}