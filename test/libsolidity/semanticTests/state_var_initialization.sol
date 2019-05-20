contract C {
    uint public i = uint(1);
    uint public k = uint(2);

    constructor() public {
        i = i + i;
        k = k - i;
    }
}
// ====
// compileViaYul: also
// ----
// i() -> 2
// k() -> 0
