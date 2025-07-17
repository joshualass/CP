auto triangle = [&](Z a) -> Z {
    return a * (a + 1) / 2;
};

auto square = [&](Z a) -> Z {
    return a * (a + 1) * (2 * a + 1) / 6;
};

auto cube = [&](Z a) -> Z {
    return a * a * (a + 1) * (a + 1) / 4;
};