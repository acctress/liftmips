def encode(pattern: str, rs: int, rt: int, rd: int, shamt: int = 0) -> int:
    bits = pattern.replace(" ", "")
    assert len(bits) == 32, f"expected 32 bits, got {len(bits)}"

    rs_bits = format(rs, "05b")
    rt_bits = format(rt, "05b")
    rd_bits = format(rd, "05b")
    sh_bits = format(shamt, "05b")

    rs_i = rt_i = rd_i = sh_i = 0
    out = []
    for ch in bits:
        if ch == "s":
            out.append(rs_bits[rs_i]); rs_i += 1
        elif ch == "t":
            out.append(rt_bits[rt_i]); rt_i += 1
        elif ch == "d":
            out.append(rd_bits[rd_i]); rd_i += 1
        elif ch == "h":
            out.append(sh_bits[sh_i]); sh_i += 1
        else:
            out.append(ch)

    word_bits = "".join(out)
    return int(word_bits, 2)


if __name__ == "__main__":
    pattern = input("pattern> ")
    rs = int(input("rs> "))
    rt = int(input("rt> "))
    rd = int(input("rd> "))
    value = encode(pattern, rs, rt, rd)
    print(f"binary : {pattern}")
    print(f"hex    : 0x{value:08X}")