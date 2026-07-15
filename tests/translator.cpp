#include <liftmips/translator.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace liftmips::decoder;
using namespace liftmips::translator;

TEST_CASE( "lift_instr translates ADDU correctly", "[translator]" )
{
    /* addu $t2, $t3, $t4 */
    /* %1 = iadd %2, %3 */

    constexpr std::uint32_t word = 0x016C6821;
    const auto instr = decode_r_type( word );

    lift_context_t ctx { };
    lift_instr( instr, ctx );

    REQUIRE( ctx.ir == "%32 = iadd %11, %12\n" );
}

TEST_CASE( "lift_instr translates SUBU correctly", "[translator]" )
{
    /* subu $t2, $t3, $t4 */
    /* %1 = isub %2, %3 */

    constexpr std::uint32_t word = 0x016C6823;
    const auto instr = decode_r_type( word );

    lift_context_t ctx { };
    lift_instr( instr, ctx );

    REQUIRE( ctx.ir == "%32 = isub %11, %12\n" );
}