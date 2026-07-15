#include <liftmips/decoder.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace liftmips::decoder;

TEST_CASE( "decode_r_type decodes ADDU correctly", "[decoder]" )
{
    /* addu $t2, $t3, $t4 */
    /*
     * rs=11 ($t3)
     * rt=12 ($t4)
     * rd=10 ($t2)
     * funct=0x21
     */

    constexpr std::uint32_t word = 0x016C5021;

    const auto instr = decode_r_type( word );

    REQUIRE( instr.op == opcode_t::ADDU );
    REQUIRE( static_cast< int >( instr.rs ) == 11 );
    REQUIRE( static_cast< int >( instr.rt ) == 12 );
    REQUIRE( static_cast< int >( instr.rd ) == 10 );
    REQUIRE( static_cast< int >( instr.shamt ) == 0 );
}

TEST_CASE( "decode_r_type decodes SUBU correctly", "[decoder]" )
{
    /* subu $t2, $t3, $t4 */
    /*
     * rs=11 ($t3)
     * rt=12 ($t4)
     * rd=10 ($t2)
     * funct=0x23
     */

    constexpr std::uint32_t word = 0x016C5023;

    const auto instr = decode_r_type( word );

    REQUIRE( instr.op == opcode_t::SUBU );
    REQUIRE( static_cast< int >( instr.rs ) == 11 );
    REQUIRE( static_cast< int >( instr.rt ) == 12 );
    REQUIRE( static_cast< int >( instr.rd ) == 10 );
    REQUIRE( static_cast< int >( instr.shamt ) == 0 );
}