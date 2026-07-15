#pragma once

#include <liftmips/decoder.hpp>
#include <string>
#include <array>
#include <format>
#include <print>

namespace liftmips::translator
{
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

    inline void lift_addu( const decoder::instr_t& instr, lift_context_t& ctx )
    {
        std::println("lifting addu");

        auto src = ctx.reg_identifiers[ instr.rs ];
        auto src2 = ctx.reg_identifiers[ instr.rt ];
        auto val = alloc_value( ctx );
        auto line = std::format( "{} = iadd {}, {}", val, src, src2 );
        ctx.reg_identifiers[ instr.rd ] = val;
        ctx.ir += line;
    }

    inline void lift_instr( const decoder::instr_t& instr, lift_context_t& ctx )
    {
        switch ( instr.op )
        {
            case decoder::opcode_t::ADDU: lift_addu( instr, ctx ); break;
        }
    }
}